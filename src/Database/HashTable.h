#ifndef HASHTABLE_H_
#define HASHTABLE_H_
//#pragma warning(disable : 4290) // Turn off the warning about exception handling. (Complier bugs)
#include <iostream>
static int nModifier = 1; // static variable which is used in ProbingFunction() method.
static int nPosNeg = +1; // static variable which is used in ProbingFunction() method.

template <typename Type> // This is a template class.
class HashTable {

	private :

		Type ** PointerList; // PointerList is an array of Type object pointers.
		int m_nSize; // Size of PointerList.
		int m_nNumItem; // Number of items in PointerList.

		int HashFunction(const string strKey) const; // Hash function that converts a key to an index of the item.
		int QuadraticProbing(const int nCrrIndex) const throw (const char *) ; // Probing function for handling collisions.

		void Expand(); // Expand when necessary.

	public :

		HashTable(); // default constructor.
		HashTable(int nSize); // parameterized constructor.
		~HashTable(); // destructor.

		void Insert(Type * const thisItem, const int nKeyType) throw (const char *); // Insert function, nKeyType decides the key value is either integer or string type.
		Type * Retrieve(Type * const thisItem, const int nKeyType) const throw (const char *); // Retrieve function, nKeyType decides the key value is either int or string type.
		int Size() const { return m_nNumItem; } // Return the number of items in PointerList.

};

// Method definitions start from here.
template <typename Type>
HashTable<Type>::HashTable() {

	m_nSize = 151; // 4j + 3, j = 37
	m_nNumItem = 0; // Set Number of Item is initially 0.

	PointerList = new Type *[m_nSize]; // a list of Type pointers.
	for (int i=0; i<m_nSize; i++) PointerList[i] = NULL; // Set all the items in PointerList pointing to NULL.

}

template <typename Type>
HashTable<Type>::HashTable(int nSize) {

	m_nSize = nSize;
	m_nNumItem = 0; // Set Number of Item is initially 0.

	PointerList = new Type *[m_nSize]; // a list of Type pointers.
	for (int i=0; i<m_nSize; i++) PointerList[i] = NULL; // Set all the items in PointerList pointing to NULL.

}

template <typename Type>
HashTable<Type>::~HashTable() {

	delete [] PointerList; // release memory.

}

template <typename Type>
int HashTable<Type>::HashFunction(const string strKey) const {

	int nKeyDigit(0); // Store the ASCII number of each character.
	int nKeySum(0); // Store the sum of the ASCII numbers of all the characters in strKey.

	for (int i=0; i<(int)strKey.length(); i++) { // loop as many as the number of character in string.

		nKeyDigit = strKey[i] + 0; // -48 converts char to int(ASCII code). i.e., "1" = 1
		nKeySum += nKeyDigit;

	}

	int nIndex = nKeySum % m_nSize; // modular function.
	return nIndex;

}

template <typename Type>
int HashTable<Type>::QuadraticProbing(const int nCrrIndex) const  throw (const char *) {

	if (nModifier > (m_nSize - 1) / 2) throw "IndexNotFoundException"; // Prevent infinite loop.

	int nNewIndex = nCrrIndex + (nModifier*nModifier*nPosNeg);
	nPosNeg *= -1; // Flip the sign of modifier.
	if (nPosNeg == +1) nModifier++; // Increase the modifier by 1.

	nNewIndex = nNewIndex % m_nSize; // If new index is out of boundary, change it validly.
	if (nNewIndex < 0) nNewIndex= m_nSize + nNewIndex + 1; // if new index is negative value, change it validly.
	return nNewIndex;

}

template <typename Type>
void HashTable<Type>::Insert(Type * const thisItem, const int nKeyType)  throw (const char *) {

	int nPossibleIndex(0);

	// Index that is initially generated by Hash function.
	if (nKeyType == 1) nPossibleIndex = HashFunction(thisItem->getKey1());
	else if (nKeyType == 2) nPossibleIndex = HashFunction(thisItem->getKey2());

	// Let nIndex = nPossibleIndex temporarily.
	int nIndex = nPossibleIndex;

	 // Loop until the nIndex is not occupied : Check if there is any collision. If there is, call a probing function.
	while (PointerList[nIndex] != NULL) nIndex = QuadraticProbing(nPossibleIndex); // Save final index to save after checking if there is any collision or not.

	PointerList[nIndex] = thisItem; // Let PointerList[nIndex] points to thisItem.

	nModifier = 1; // Reset the nModifier to 1.
	nPosNeg = +1;
	m_nNumItem++; // Increase m_nNumItem by 1.

}

template <typename Type>
Type * HashTable<Type>::Retrieve(Type * const thisItem, const int nKeyType) const  throw (const char *) {

	try {

		int nPossibleIndex(0);
		int nIndex(0);

		if (nKeyType == 1) {

			nPossibleIndex = HashFunction(thisItem->getKey1());
			nIndex = nPossibleIndex;

			while ((PointerList[nIndex] != NULL) && (thisItem->getKey1() != PointerList[nIndex]->getKey1())) nIndex = QuadraticProbing(nPossibleIndex);

		}

		else if (nKeyType == 2) {

			nPossibleIndex = HashFunction(thisItem->getKey2());
			nIndex = nPossibleIndex;

			while ((PointerList[nIndex] != NULL) && (thisItem->getKey2() != PointerList[nIndex]->getKey2())) nIndex = QuadraticProbing(nPossibleIndex);

		}

		nModifier = 1;
		nPosNeg = +1;

		if ((nIndex >= m_nSize) || (PointerList[nIndex] == NULL)) throw "ItemNotFoundException"; // more exception.

		return PointerList[nIndex];

	}

	catch (const char *) {

		throw "ItemNotFoundException";

	}

}

template <typename Type>
void HashTable<Type>::Expand() {

	m_nSize = 2 * m_nSize;
	m_nNumItem = 0; // Set Number of Item is initially 0.

	Type ** TempPointerList = new Type *[m_nSize]; // a list of Type pointers.
	for (int i=0; i<m_nSize; i++) TempPointerList[i] = NULL; // Set all the items in PointerList pointing to NULL.

}

#endif