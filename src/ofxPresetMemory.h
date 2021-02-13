#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace ofx { namespace preset {
template<typename Key>
class PresetBase
{
public:
	virtual bool update(const Key &key) = 0;
};
template<typename Value, typename Key=std::string>
class Preset : public PresetBase<Key>
{
public:
	Preset(Value &&value): value_(value), ref_(value_){}
	Preset(Value &value): value_(value), ref_(value){}
	bool set(const Key &key, Value value) {
		return storage_.insert(std::make_pair(key, value)).second;
	}
	template<typename ...Args>
	bool set(const Key &key, Args &&...args) {
		return set(key, Value{std::forward<Args>(args)...});
	}
	Value& get() {
		return ref_;
	}
	Value get(const Key &key) {
		return storage_[key];
	}
	bool update(const Key &key) override {
		auto result = storage_.find(key);
		if(result == std::end(storage_)) {
			return false;
		}
		ref_ = result->second;
		return true;
	}
protected:
	std::map<Key, Value> storage_;
	Value value_, &ref_;
};

template<typename Key>
class PresetGroup
{
public:
	void add(PresetBase<Key> &preset) {
		update_func_.emplace_back([&preset](const Key &key) {
			preset.update(key);
		});
	}
	void update(const Key &key) {
		for(auto &&f : update_func_) {
			f(key);
		}
	}
protected:
	std::vector<std::function<void(const Key&)>> update_func_;
};

template<typename Key, typename GroupKey=Key>
class PresetMemory : public PresetGroup<Key>
{
public:
	template<typename Value>
	std::shared_ptr<Preset<Value, Key>> add(const GroupKey &key, Value &&value) {
		return addToGroup(key, std::make_shared<Preset<Value, Key>>(std::move(value)));
	}
	template<typename Value>
	std::shared_ptr<Preset<Value, Key>> add(const GroupKey &key, Value &value) {
		return addToGroup(key, std::make_shared<Preset<Value, Key>>(value));
	}
	template<typename Value, typename ...Args>
	std::shared_ptr<Preset<Value, Key>> add(const GroupKey &key, Args &&...args) {
		return addToGroup(key, std::make_shared<Preset<Value, Key>>(Value{std::forward<Args>(args)...}));
	}
	template<typename Value>
	std::shared_ptr<Preset<Value, Key>> get(const GroupKey &key) {
		return std::static_pointer_cast<Preset<Value, Key>>(presets_[key]);
	}
protected:
	std::map<GroupKey, std::shared_ptr<PresetBase<Key>>> presets_;

private:
	template<typename Value>
	std::shared_ptr<Preset<Value, Key>> addToGroup(const GroupKey &key, std::shared_ptr<Preset<Value, Key>> preset) {
		auto result = presets_.insert(std::make_pair(key, preset));
		if(result.second) {
			PresetGroup<Key>::add(*preset);
		}
		return preset;
	}
};

}}

template<typename Value>
using ofxPreset = ofx::preset::Preset<Value, std::string>;

using ofxPresetMemory = ofx::preset::PresetMemory<std::string>;
