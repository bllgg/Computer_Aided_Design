#include "ModelPart.h"

// Creates a Model Part
ModelPart::ModelPart(const string& name) {
    this->name = name;
    this->numProperties = 0;
    this->properties = nullptr;
}

// Destroys a Model Part and all parts underneath including
// deleting children and properties
ModelPart::~ModelPart() {
    // Delete model part property
    delete[] this->properties;

    // delete vector
    for (auto p : this->children)
    {
        delete p;
    }
    this->children.clear();
}

// Sets the part name
void ModelPart::setName(const string& name) {
    this->name = name;
}

// Gets the part name
string ModelPart::getName() const {
    return this->name;
}

// Searches through the children recursively and returns the part.
// If the part is not found, this method returns NULL.
ModelPart* ModelPart::getPart(const string& partName) {
    for (int i = 0; i < children.size(); i++) {
        if (partName == this->children[i]->getName()){
            return children[i];

        } else if(children[i]->children.size() != 0){
            ModelPart * part = this-> children[i]->getPart(partName);
            if(part == nullptr){
                continue;
            }
            return part;
        }
    }
    return nullptr;
}

// Adds a part to the children
void ModelPart::addChild(ModelPart* part) {
    this->children.push_back(part);
}

// Returns ModelPart hierarchy recursively in JSON format
string ModelPart::toJSON() const {
    string prefix = "{"+getJsonString("name")+":"+getJsonString(this->getName());
    string proper = "";
    if (this->numProperties > 0){
        int i;
        for (i = 0; i < this->numProperties; ++i) {
            proper.append(",");
            proper.append(getJsonString(this->properties[i].key));
            proper.append(":");
            proper.append(getJsonString(this->properties[i].value));
        }
    }

    string child = "";
    if(!children.empty()) {
        string pre = ","+getJsonString("children")+":[";
        child.append(pre);

        for (int i = 0; i < children.size(); i++) {
            if (i != 0){
                child.append(",");
            }
            child.append(children[i]->toJSON());
        }
        child.append("]");
    }

    string postfix = "}";
    string result = prefix + proper + child + postfix;
    return result;
}

// Loops through properties and returns the value with the associated key
string ModelPart::getPropertyValue(const string& key) const {
    int len_prop;
    for (len_prop = 0; len_prop < this->numProperties; len_prop++) {
        if (key == this->properties[len_prop].key){
            return this->properties[len_prop].value;
        }
    }
    return "";
}

// Adds a property to the part and resizes the properties array
// (Allocate a new array, copy the old array, then delete the old array)
void ModelPart::addProperty(ModelPartProperty prop) {
    auto tmp_prop = new ModelPartProperty[this->numProperties+1];
    int len = 0;
    for (len = 0; len < this->numProperties; len++) {
        tmp_prop[len].value = properties[len].value;
        tmp_prop[len].key = properties[len].key;
    }
    tmp_prop[len].key = prop.key;
    tmp_prop[len].value = prop.value;
    this->numProperties = ++len;
    delete [] this->properties;
    properties = tmp_prop;
}