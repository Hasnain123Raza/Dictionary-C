#include "BinarySearchTree.h"

int main(void)
{
    Dictionary *dictionary = createDictionary("Bank", "The land alongside or sloping down to a river or lake");
    insertDefinitionDictionary(dictionary, "Bank", "A slope, mass, or mound of a particular substance");
    insertDefinitionDictionary(dictionary, "Bank", "A financial establishment");

    insertWordDictionary(dictionary, "Station", "A regular stopping place on a public transportation route");
    insertDefinitionDictionary(dictionary, "Station", "A place or building where a specified activity or service is based");

    insertWordDictionary(dictionary, "Life", "The condition that distinguishes animals and plants from inorganic matter");
    insertDefinitionDictionary(dictionary, "Life", "The existence of an individual human being or animal");
    insertDefinitionDictionary(dictionary, "Life", "The period between the birth and death of a living thing, especially a human being");

    insertWordDictionary(dictionary, "Fire", "Combustion or burning");
    insertDefinitionDictionary(dictionary, "Fire", "A burning sensation in the body");
    insertDefinitionDictionary(dictionary, "Fire", "Discharge a gun or other weapon");

    insertWordDictionary(dictionary, "Free", "Not under the control or in the power of another");
    insertDefinitionDictionary(dictionary, "Free", "Not or no longer confined or imprisoned");
    insertDefinitionDictionary(dictionary, "Free", "Without cost or payment");

    insertWordDictionary(dictionary, "Stream", "A small, narrow river");
    insertDefinitionDictionary(dictionary, "Stream", "A continuous flow of liquid, air, or gas");
    insertDefinitionDictionary(dictionary, "Stream", "Run or flow in a continuous current in a specified direction");

    return 0;
}