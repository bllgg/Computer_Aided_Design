#include <iostream>
#include "ModelPart.h"

using namespace std;

ModelPart* createWing(const string& name);

int main()
{
    ModelPart* airplane = new ModelPart("Airplane");
    airplane->addChild(new ModelPart("Fuselage"));
    airplane->addChild(new ModelPart("Wings"));
    airplane->addChild(new ModelPart("Tail"));

    ModelPart* fuselage = airplane->getPart("Fuselage");
    fuselage->addChild(new ModelPart("Cockpit"));
    fuselage->addChild(new ModelPart("Cabin"));

    ModelPart* wing = new ModelPart("R_Wing");
    wing->addChild(new ModelPart("Engine 1"));
    wing->addChild(new ModelPart("Engine 2"));
    wing->addChild(new ModelPart("Flaps"));
    wing->addChild(new ModelPart("Aileron"));

    ModelPart* wings = airplane->getPart("Wings");
    wings->addChild(createWing("LeftWing"));
    wings->addChild(createWing("RightWing"));

    ModelPart* tail = airplane->getPart("Tail");
    tail->addChild(new ModelPart("Tailplane"));
    tail->addChild(new ModelPart("Elevator"));
    tail->addChild(new ModelPart("Rudder"));
    tail->addChild(new ModelPart("Fin"));

    // Add properties
    ModelPart* cabin = airplane->getPart("Cabin");
    cabin->addProperty(ModelPartProperty("windows","25"));
    cabin->addProperty(ModelPartProperty("seats","250"));

    ModelPart* cockpit = airplane->getPart("Cockpit");
    cockpit->addProperty(ModelPartProperty("width","15"));
    cockpit->addProperty(ModelPartProperty("length","15"));

    cout << airplane << endl;
    cout << airplane->getPart("LeftWing") << endl;
    cout << airplane->getPart("RightWing") << endl;
    cout << cabin << endl;
    cout << cockpit << endl;
    cout << tail << endl;
    cout << wings << endl;

    delete airplane;

    return 0;
}

ModelPart* createWing(const string& name) {
    ModelPart* wing = new ModelPart(name);
    wing->addChild(new ModelPart("Engine 1"));
    wing->addChild(new ModelPart("Engine 2"));
    wing->addChild(new ModelPart("Flaps"));
    wing->addChild(new ModelPart("Aileron"));
    return wing;
}