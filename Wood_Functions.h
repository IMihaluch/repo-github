#include <cstdlib>
using namespace std;

class Wood_Functions 
{
public:

Wood_Functions() {}

	Wood_Functions (int nodesQuantity, int range) 
	{
		 if( nodesQuantity > range) {
			
cout << "Wrong!\n";

return;
}

		if (nodesQuantity > 0) 
		
		{
			for (int a = 0; a < nodesQuantity; a++) {
				
				while(!enter(r() % range)) {}
			}
		}
	}

	bool enter(int value) {
		Node * node = (Node*) malloc(sizeof(Node));
		if(!node) 
		{
cout << "Failed!";
			return false;
		}
		node->value = value;
		node->left = NULL;
		node->right = NULL;

		if(!root) {
			root = node;
			nodesCount++;
			return true;
		} else {
			Node * current = root;
			do {
				if (value == current->value) {
					
			return false;
				} 

				else if(value < current->value) {
					
					if(!current->left) {
					
					current->left = node;
					
					nodesCount++;
						
	       return true;
					}
					current = current->left;
				} 

				else {
					if(!current->right) {
					
			current->right = node;						
			nodesCount++;
						
		return true;
					}
					current = current->right;
				}
				
			} while(true);			
		}

		return false;
	}

	void print() 
	{
		if(!root) 
		{
			cout << "Empty!\n";
		return;
		}

		printWithBraces(root);

		cout << "\n Quantitye lements: " << nodesCount << "\n";
	}

	void balance() 
	{
		if(!root) return;
		
		int count = nodesCount;
		int tmp [count] = {0};
		int currentId = 0;	

		extractValue(root, tmp, currentId);

		
		balanceInsertNext(tmp, 0, count - 1);
	}

	
	bool checkBalance(bool printResult = false) {
		
		int balanceLayer = countBalanceLayer();
		
		int maxLayer = countMaxLayer();
		
		if(printResult) 
		{
cout 	<< "Balance layer : " << balanceLayer << ", max layer: " << maxLayer << ", tree is " << (maxLayer > balanceLayer ? "not " : "") << "balanced\n";
		}

		return maxLayer == balanceLayer;
	}

	bool find (int value) {
		
		if(!root) return false;
		
		return findNext(root, value);
	}

	private:
	
	typedef struct Node {
		
		int value;
		
		struct Node * left;
		
		struct Node * right;
	} Node;

	void printWithBraces(Node * current) {
		
		cout << current->value << "(";
		 
		       if(current->left) {
			
			printWithBraces(current->left);
		} 
		else cout << "*";
		
      cout << ",";
		
		       if(current->right) {
			
			printWithBraces(current->right);
		}       
		else cout << "*";
		
		cout << ")";
	}

	int countBalanceLayer() {
		
		if(!nodesCount) return 0;

		int balanceLayer = 0;
		
		int temp = nodesCount;
		
		int nodesOnLevel = 1;

		while(temp > 0) {
			
			temp = temp - nodesOnLevel;
			
			nodesOnLevel = nodesOnLevel << 1;
			
			balanceLayer++;
		}

		return balanceLayer;
	}

	int countMaxLayer() {
		
		if(!nodesCount) return 0;

		int layersCount = 1;
		
		int currentLayer = 1;
		
		countNext(root, currentLayer, layersCount);
		
		return layersCount - 1;
	}

	void countNext(Node * current, int &currentLayer, int &maxLayer) 
	{
		
		currentLayer++;
		
		if(current->left) countNext(current->left, currentLayer, maxLayer);
		
		if(current->right) countNext(current->right, currentLayer, maxLayer);

		maxLayer = maxLayer > currentLayer ? maxLayer : currentLayer;
		
		currentLayer--;
	}

	void extractValue(Node * current, int * arr, int &id) 
	{
		
	if(current->left) extractValue(current->left, arr, id);
		
		arr[id++] = current->value;
		
		if(current->right) extractValue(current->right, arr, id);
	}
	

	void balanceInsertNext(int * arr, int minId, int maxId) {
		int mid = minId + (maxId - minId) / 2;		

		if(mid - minId > 0) {
		enter(arr[mid]);
			balanceInsertNext(arr, minId, mid - 1);
		} else {
			for(int a = minId; a <= maxId; a++) enter(arr[a]);
		}

		if(maxId - mid > 0) {
			enter(arr[mid]);
			balanceInsertNext(arr, mid + 1, maxId);
		} else {
			for(int a = minId; a <= maxId; a++) enter(arr[a]);
		}
	}

	
	bool findNext(Node * current, const int &value) {
		if(value == current->value) return true;
		else if(value < current->value) {
			if(!current->left) return false;
			return findNext(current->left, value);
		} else {
			if(!current->right) return false;
			return findNext(current->right, value);
		}
	}

	Node * root = NULL;
	int nodesCount = 0;
};
