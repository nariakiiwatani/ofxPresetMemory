# ofxPresetMemory

```
ofxPresetMemory preset_;
int test_;


void ofApp::setup(){
	// initializing presetable value named "int" with an integer reference(test_)
	auto intarg = preset_.add("int", test_);
	// set each preset with a name
	for(int i = 0; i < 10; ++i) {
		intarg->set(ofToString(i), i*2);
	}
	// you can add presetable value without owning a variable
	auto vec2arg = preset_.add<glm::vec2>("vec2", 0, 0);
	// or this way
//	auto vec2arg = preset_.add("vec2", glm::vec2{0, 0});
	for(int i = 0; i < 10; ++i) {
		vec2arg->set(ofToString(i), {i*5,i*10});
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("press [0-9] to select preset", 10, 10);
	// you can get the value via a reference(test_) you passed when initializing
	ofDrawBitmapString("intarg:  " + ofToString(test_), 10, 20);
	// or you can grab whole instance so that you can get the value with get()
	auto vec2arg = preset_.get<glm::vec2>("vec2");
	ofDrawBitmapString("vec2arg: " + ofToString(vec2arg->get()), 10, 30);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// update preset values with certain key
	preset_.update(ofToString(key-'0'));
}

```

## API

### ofxPreset

It holds one set of presets for a value or reference.  
If you have this;
```
ofxPreset<int> preset(0);
``` 
You can set values by like;
```
preset.set("one", 1);
preset.set("fake prime", 57);
```
You can get the value by;
```
preset.get("one"); // 1
preset("fake prime"); // 57
```
Or
```
preset.update("one");
preset.get(); // 1
preset.update("fake prime");
preset.get(); // 57
```
Or if you create ofxPreset by a lvalue reference like this;
```
int value = 0;
ofxPreset<int>(value);
```
And add presets in same way;
```
preset.set("one", 1);
preset.set("fake prime", 57);
```
You can get these values directly via `value`;
```
preset.update("one");
value; // 1
preset.update("fake prime");
value; // 57
```

