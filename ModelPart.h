#ifndef MODEL_PART_H_
#define MODEL_PART_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// A model property data structure
struct ModelPartProperty {
    ModelPartProperty() {}
    ModelPartProperty(const string& k, const string& v) {
        key = k;
        value = v;
    }
    string key;
    string value;
};

class ModelPart {
public:
    // 1. Creates a Model Part and initializes variables
    ModelPart(const string& name);

    // 2. Destroys a Model Part and all parts underneath including
    // deleting children and properties array
    ~ModelPart();

    // 3. Sets the part name
    void setName(const string& name);

    // 4. Gets the part name
    string getName() const;

    // 5. Adds a part to the children
    void addChild(ModelPart* part);

    // 6. Searches through the children recursively and returns the part.
    // If the part is not found, this method returns NULL.
    ModelPart* getPart(const string& partName);

    // 7. Returns ModelPart hierarchy recursively in JSON format:
    // {"name"="partName","prop1"="val1","prop2"="val2","children"=[{"name"="child1" ...},{"name"="child2 ...}]}
    string toJSON() const;

    // 8. Loops through properties and returns the value with the associated key
    // Returns "" if property is not found;
    string getPropertyValue(const string& key) const;

    // 9. Adds a property to the part and resizes the properties array
    // (Allocate a new array, copy the old array, then delete the old array,
    // finally set the properties array to the new one)
    void addProperty(ModelPartProperty prop);


public:
    const vector<ModelPart*>& getChildren() const { return children; }

private:
    // Helper function for writing JSON strings outputs string with the value: "str"
    string getJsonString(const string& str) const {return "\"" + str + "\""; }

private:
    string name;
    vector<ModelPart*> children;
    ModelPartProperty* properties;
    int numProperties;
};


// Used for printing ModelPart to output stream
inline void printPartOutput(ostream& os, const ModelPart& part, int level = 0) {
    const vector<ModelPart*>& children = part.getChildren();
    string tab = "";
    for (int i = 0; i < level; i++) {
        tab += "   ";
    }
    os << tab << part.getName() << endl;
    for (int i = 0; i < children.size(); i++) {
        printPartOutput(os, *children[i], level + 1);
    }
}

inline ostream& operator<<(ostream& os, const ModelPart& part) {
    printPartOutput(os, part);
    os << part.toJSON() << endl;
    return os;
}

inline ostream& operator<<(ostream& os, const ModelPart* part) {;
    os << *part;
    return os;
}

#endif // MODEL_PART_H_

