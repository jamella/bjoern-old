#ifndef _BJOERN_FUNCTION_NODE_HPP
#define _BJOERN_FUNCTION_NODE_HPP

#include <list>
#include <map>
#include <string>

using namespace std;

class BjoernFunctionNode : public BjoernNode {
private:
	string name;
	list<BjoernBasicBlockNode *> basicBlocks;
	map<string, BjoernBasicBlockNode *> addrToBB;
	map<string, BjoernSymbolNode *> symbolToNode;
public:

	BjoernFunctionNode() : BjoernNode()
	{
		type = "FunctionDef";
	}

	void setName(string &aName)
	{
		name = aName;
	}

	const string & getName()
	{
		return name;
	}

	void addBasicBlock(BjoernBasicBlockNode *basicBlock)
	{
		basicBlocks.push_back(basicBlock);
		addrToBB[basicBlock->getAddr()] = basicBlock;
	}

	void addSymbol(string &symbol)
	{
		// Return if symbol is already
		// registered

		auto it = symbolToNode.find(symbol);
		if(it != symbolToNode.end())
			return;

		BjoernSymbolNode *symbolNode = new BjoernSymbolNode();
		symbolNode->setAddr(symbol);
		symbolToNode[symbol] = symbolNode;

	}

	BjoernSymbolNode *getSymbolNodeByName(const string & name)
	{
		return symbolToNode[name];
	}

	BjoernBasicBlockNode *getBasicBlockByAddr(const string &addr)
	{
		auto it = addrToBB.find(addr);
		if(it == addrToBB.end())
			return NULL;
		return it->second;
	}

	const list<BjoernBasicBlockNode *> & getBasicBlocks()
	{
		return basicBlocks;
	}

	map<string, BjoernSymbolNode *> & getSymbolToNode()
	{
		return symbolToNode;
	}

	BjoernBasicBlockNode *getEntryBlock() const
	{
		if(basicBlocks.size() == 0)
			return NULL;

		return basicBlocks.front();
	}

	void setFunctionIdOfChildren()
	{
		std::list<BjoernBasicBlockNode *>::const_iterator it;
		for (it = basicBlocks.begin(); it != basicBlocks.end(); ++it) {
			BjoernBasicBlockNode *node = *it;
			node->setFunctionId(id);
		}
	}


	~BjoernFunctionNode()
	{
		freeBasicBlocks();
	}

	void freeBasicBlocks()
	{
		std::list<BjoernBasicBlockNode *>::const_iterator it;
		for (it = basicBlocks.begin(); it != basicBlocks.end(); ++it) {
			delete *it;
		}
	}

};

#endif
