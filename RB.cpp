#include<iostream>

using namespace std;

struct node
{
       int key;
       node *parent;
       char color;
       node *left;
       node *right;
};
class RBtree
{
      node *root;
   public :
      RBtree()
      {
              root=NULL;
      }
      void insert(node * );
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void transplant(node *,node *);
      void del(int );
      node *tree_minimum(node *);
      void delfix(node *);
      void disp();
      void display( node *);
};
void RBtree::insert(node *z)
{
	//recibimos clave y lo almacenamos en un nodo
  int clave;cin>>clave;
	z->key=clave;
  
	 //ahora seguimos con el algotimo de insercion
     node *y=NULL;
     node *x=root;

     if(root==NULL){
        root=z;
        z->parent=NULL;
     }

     else{
     while(x!=NULL){
        y=x;  
    
        if(z->key<x->key){x=x->left;}
        else{x=x->right;}
    }
   
    z->parent=y;
   
    //Si el padre que es y, es null indica que aun no se han insertado nodos,entonces se inserta en la raiz
    if(y==NULL){root=z;}
    else if(z->key<y->key){y->left=z;}
    else{
    
      y->right=z;
    }
   }
    z->left=NULL;
    z->right=NULL;
    /* Al nuevo nodo se le da el color rojo,de esta manera no se viola ninguna condicion
    a excepcion de la primera(el padre del nodo insertado puede ser rojo),se llama a insertfix*/


    z->color='r';

     insertfix(z);
}

void RBtree::insertfix(node *z)
{
     node *u;
     if(root==z){
      z->color='b';return;

     }
    
     while(z->parent!=NULL && z->parent->color=='r'){
      if(z->parent==NULL){break;}

        if(z->parent==z->parent->parent->left){

          if(z->parent->parent->right!=NULL){
            u=z->parent->parent->right;
            if(u->color=='r'){
              
                z->parent->color='b';
                u->color='b';
                z->parent->parent->color='r';
                z=z->parent->parent;
            }
          }
            else
            { 
              if(z->parent->right==z){ 
                  z=z->parent;
                  leftrotate(z);
                }
                  z->parent->color='b';
                  z->parent->parent->color='r';
                  rightrotate(z->parent->parent);
            }
          }

        else{ 
            if(z->parent->parent->left!=NULL)
            {
              u=z->parent->parent->left;
              if(u->color=='r'){
                z->parent->color='b';
                u->color='b';
                z->parent->parent->color='r';
                z=z->parent->parent;
              }
          }
          else {
            if(z==z->parent->left){
              z=z->parent;
              rightrotate(z);
            }
            z->parent->color='b';
             z->parent->parent->color='r';
            leftrotate(z->parent->parent);
          }

        }

     root->color='b';
  
  }
}


    
     





void RBtree::transplant(node *u,node*v){
      if(u->parent==NULL){
        root=v;
      }
      else if(u==u->parent->left){
        u->parent->left=v;
      }
      else{u->parent->right=v;}
      v->parent=u->parent;


}





void RBtree::del(int clave)
{
    

	    node *x;
	    char ycor;		
      node *y;
      node *z=root;
      

      while(z!=NULL)
      {
        if(z->key>clave){z=z->right;}
        else if(z->key<clave){z=z->left;}
        else{break;}

      }
      if(z==NULL){return;}


      y=z;
      ycor=y->color;
      if(z->left==NULL){
      		x=z->right;
      		transplant(z,z->right);
      }
      else if(z->right==NULL){
      		x=z->left;
      		transplant(z,z->left);
      }
      else{
      		y=tree_minimum(z->right);
      		ycor=y->color;
      		x=y->right;
      		if(y->parent==z){x->parent=y;}
      		else{
      			transplant(y,y->right);
      			y->right=z->right;
      			y->right->parent=y;
      		}
      		transplant(z,y);
      		y->left=z->left;
      		y->left->parent=y;
      		y->color=z->color;


      }
      delete z;
      if(ycor=='b'){
      	delfix(x);
      }

    }
  



node* RBtree::tree_minimum(node *x){
      while(x->left!=NULL){x=x->left;}
      return x;



}


void RBtree::delfix(node *x)
{
	node *w=new node;
	while(x!=root && x->color=='b'){
		if(x==x->parent->left){
				w=x->parent->right;
				if(w->color=='r'){
					w->color='b';
					x->parent->color='r';
					leftrotate(x->parent);
					w=x->parent->right;
				}
				if( w->left->color=='b'&&  w->right->color=='b'){
					w->color='r';
					x=x->parent;
				}

				else {
          if( w->right->color=='b'){
						w->left->color='b';
						w->color='r';	
						rightrotate(w);
						w=x->parent->right;
           }
					w->color=x->parent->color;
					x->parent->color='b';
					w->right->color='b';
					leftrotate(x->parent);
					x=root;

				}
		}

    else{

      w=x->parent->left;
        if(w->color=='r'){
          w->color='b';
          x->parent->color='r';
          rightrotate(x->parent);
          w=x->parent->left;
        }
        if(w->right->color=='b'&& w->left->color=='b'){
          w->color='r';
          x=x->parent;
        }

        else {
          if( w->left->color=='b'){
            w->right->color='b';
            w->color='r'; 
            leftrotate(w);
            w=x->parent->left;
           }
          w->color=x->parent->color;
          x->parent->color='b';
          w->left->color='b';
          rightrotate(x->parent);
          x=root;

        }


    }

	
	}

	x->color='b';



}




void RBtree::leftrotate(node *x)
{
     node *y=new node;
     y=x->right;
     x->right=y->left;
     if(y->left!=NULL){y->left->parent=x;}
     y->parent=x->parent;
     if(x->parent==NULL){root=y;}
     else{x->parent->right=y;}
     y->left=x;
     x->parent=y;



}
void RBtree::rightrotate(node *x)
{
     node *y=new node;
     y=x->left;
     x->left=y->right;
     if(y->right!=NULL){y->right->parent=x;}
     y->parent=x->parent;
     if(x->parent==NULL){root=y;}
     else{x->parent->left=y;}
     y->right=x;
     x->parent=y;


}


void RBtree::disp()
{
     display(root);
}
void RBtree::display(node *p)
{
     if(root==NULL)
     {
          cout<<"\nARBOL VACIO.";
          return ;
     }
     if(p!=NULL)
     {
                cout<<"\n\t NODO: ";
                cout<<"\n LLAVE: "<<p->key;
                cout<<"\n COLOR: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Padre: "<<p->parent->key;
              
                if(p->right!=NULL)
                       cout<<"\n Hijo derecho: "<<p->right->key;
                else
                       cout<<"\n Este no tiene hijo derecho .  ";
                if(p->left!=NULL)
                       cout<<"\n Hijo izquierdo: "<<p->left->key;
                else
                       cout<<"\n Este no tiene hijo izquierdo .  ";
                cout<<endl;
    if(p->left)
    {
                 cout<<"\n\nIzquierda:\n";
     display(p->left);
    }
    /*else
     cout<<"\nNo Left Child.\n";*/
    if(p->right)
    {
     cout<<"\n\nDerecha:\n";
                 display(p->right);
    }
    /*else
     cout<<"\nNo Right Child.\n"*/
     }



}




int main()
{
//7 8 3 2 1 11 15 
    
RBtree arbol;

node *a=new node;
node *b=new node;
node *c=new node;
node *d=new node;
node *e=new node;
node *f=new node;
node *g=new node;


arbol.insert(a);
arbol.insert(b);
arbol.insert(c);
arbol.insert(d);
arbol.insert(e);
arbol.insert(f);
arbol.insert(g);



arbol.disp();
arbol.del(7);
cout<<"**************************************"<<endl;
arbol.disp();
//cout<<"**************************************"<<endl;

//arbol.del(2);




/*

arbol.insert(7);
arbol.insert(8);
arbol.insert(3);
arbol.insert(2);
arbol.insert(1);
arbol.insert(11);
arbol.insert(15);
arbol.insert(0);
arbol.insert(-1);
arbol.insert(16);
arbol.insert(17);
arbol.insert(18);
arbol.disp();


*/




}
