#include <iostream> 
#include<climits>


using namespace std; 
  
// Structure to represent an interval 
struct Interval 
{ 
    int low, high; 
}; 
  
// Structure to represent a node in Interval Search Tree 
struct ITNode 
{ 
    Interval *i;  // 'i' could also be a normal variable 
    int max; 
    ITNode *left, *right; 
}; 
  
// A utility function to create a new Interval Search Tree Node 
ITNode * newNode(Interval i) 
{ 
    ITNode *temp = new ITNode; 
    temp->i = new Interval(i); 
    temp->max = i.high; 
    temp->left = temp->right = NULL; 
}; 
  
// A utility function to insert a new Interval Search Tree Node 
// This is similar to BST Insert.  Here the low value of interval 
// is used tomaintain BST property 
ITNode *insert(ITNode *root, Interval i) 
{ 
    // Base case: Tree is empty, new node becomes root 
    if (root == NULL) 
        return newNode(i); 
  
    // Get low value of interval at root 
    int l = root->i->low; 
  
  
    // If root's low value is smaller, then new interval goes to 
    // left subtree 
    if (i.low < l) {
    	
    	
        root->left = insert(root->left, i); 
  }
    // Else, new node goes to right subtree. 
    else
        root->right = insert(root->right, i); 
  
    // Update the max value of this ancestor if needed 
    if (root->max < i.high) 
    	
    	
        root->max = i.high; 
  
    return root; 
} 
  
// A utility function to check if given two intervals overlap 
bool doOVerlap(Interval i1, Interval i2) 
{ 
    if (i1.low <= i2.high && i2.low <= i1.high) 
        return true; 
    return false; 
} 
  
// The main function that searches a given interval i in a given 
// Interval Tree. 
Interval *overlapSearch(ITNode *root, Interval i) 
{ 
    // Base Case, tree is empty 
    if (root == NULL) return NULL; 
  
    // If given interval overlaps with root 
    if (doOVerlap(*(root->i), i)) 
        return root->i; 
  
    // If left child of root is present and max of left child is 
    // greater than or equal to given interval, then i may 
    // overlap with an interval is left subtree 
    if (root->left != NULL && root->left->max >= i.low) 
        return overlapSearch(root->left, i); 
  
    // Else interval can only overlap with right subtree 
    return overlapSearch(root->right, i); 
} 



void intervalSearch(ITNode *root, Interval in[],int n){

	for(int i=0;i<n;i++){
		Interval *res=overlapSearch(root,in[i]);
		if(res==NULL){continue;}
		else{
		cout << "\nSearching for interval [" << in[i].low << "," << in[i].high << "]"; 
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]"<<endl; 
		}


	}
	
}





void inorder(ITNode *root) 
{ 
    if (root == NULL) return; 
  
    inorder(root->left); 
  
    cout << "[" << root->i->low << ", " << root->i->high << "]"
         << " max = " << root->max << endl; 
  
    inorder(root->right); 
} 
  

// Driver program to test above functions 

ITNode *minimointerval(ITNode *node){

	ITNode *aux=node;
	while(aux->left!=NULL){aux=aux->left;}
	return aux;
}

int buscarmaximo(int a,int b,int c){
	if(a>b){
		if(a>c){
			return a;
		}
		return c;
	}
	else{
		if(b>c){return b;}
		return c;
	}

}




ITNode *deletee(ITNode *root,Interval i){
	if(root==NULL){
		return NULL;}
	if(i.low<(root->i)->low){
		root->left=deletee(root->left,i);
	}

	else if(i.low>(root->i)->low){
		root->right=deletee(root->right,i);
	}
	else if(i.low==(root->i)->low && i.high==(root->i)->high){
		if(root->left==NULL){
			ITNode *temp=root->right;
			delete root;
			return temp;
		}
		else if(root->right==NULL){
			ITNode *temp=root->left;
			delete root;
			return temp;
		}

		ITNode *temp=minimointerval(root->right);
		root->i=temp->i;
		root->right=deletee(root->right,*(temp->i));
	}


	if(root->left!=NULL){
			if(root->i->high>root->left->max){
				root->max=root->i->high;
			}



	}
	root->max=buscarmaximo(root->i->high,((root->left!=NULL)?root->left->max:INT_MIN),((root->right!=NULL)?root->right->max:INT_MIN));
	return root;
/*
	if(root->left!=NULL){
		if(root->i->high>root->left->max){
			if(root->right!=NULL){
				if(root->i->high>root->right->max){root->max=root->i->high;}
				else{root->max=root->right->max;}
			}
			else{

				root->max=root->i->high;
			}		
		}

		else{
			if(root->left!=NULL){
				if(root->right!=NULL){
					if(root->left->max>root->right->max){
						root->max=root->left->max;
					}
					else{root->max=root->right->max;}
				}

			}

		}


	}
	else{

		if(root->i->high>INT_MIN){
			if(root->right!=NULL){
				if(root->i->high>root->right->max){root->max=root->i->high;}
				else{root->max=root->right->max;}
			}
			else{

				root->max=root->i->high;
			}		
		}

		else{
			if(root->left!=NULL){
				if(root->right!=NULL){
					if(root->left->max>root->right->max){
						root->max=root->left->max;
					}
					else{root->max=root->right->max;}
				}


			}

		}



	}
	*/


}






int main() 
{ 
    // Let us create interval tree shown in above figure 
    Interval ints[] = {{15, 20}, {10, 30}, {17, 19}, 
        {5, 20}, {12, 15}, {30, 40} 
    }; 
    int n = sizeof(ints)/sizeof(ints[0]); 
    ITNode *root = NULL; 
    for (int i = 0; i < n; i++) 
        root = insert(root, ints[i]); 
  
    cout << "Inorder traversal of constructed Interval Tree is\n"; 
    cout<<root->i->low<<root->i->high<<endl;
    inorder(root); 
  
    Interval x = {1, 4}; 
  
    cout << "\nSearching for interval [" << x.low << "," << x.high << "]"; 
    Interval *res = overlapSearch(root, x); 
    if (res == NULL) 
        cout << "\nNo Overlapping Interval"; 
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]"<<endl; 

    


    Interval z= {5, 20};
    cout << "\nDeleting interval [" << z.low << "," << z.high << "]";
    deletee(root,z);
     cout << "\nInorder traversal of constructed Interval Tree is\n";
    inorder(root);
    
    intervalSearch(root,ints,n);

    return 0; 




}

/*
Tarea:
1) Pasar el código al código a clases. (Opcional) Puede ser a partir de la clase abstracta de BinaryTree del libro.
2) Implemente el método delete  para el  intervaltree.
3) Extender el método intervalSearch() para que imprima todos los intérvalos en lugar de uno.
*/
