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
              root=nullptr;
      }
      void insert(int);
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
void RBtree::insert(int clave)
{
    cout<<clave<<endl;
  //recibimos clave y lo almacenamos en un nodo
    node *z=new node;
    z->key=clave;
    z->color='r';

    z->left=z->right=z->parent=nullptr;

   //ahora seguimos con el algotimo de insercion
     node *y=nullptr;
     node *x=this->root;


    while(x!=nullptr){
        y=x;
        if(z->key<x->key){
            x=x->left;
        }
        else
            x=x->right;
    }

    z->parent=y;

    //Si el padre que es y, es null indica que aun no se han insertado nodos,entonces se inserta en la raiz
    if(y==nullptr){
        this->root=z;}
    else if(z->key<y->key){
        y->left=z;}
    else{

      y->right=z;
    }

    z->left=nullptr;
    z->right=nullptr;
    z->color='r';
    /* Al nuevo nodo se le da el color rojo,de esta manera no se viola ninguna condicion
    a excepcion de la primera(el padre del nodo insertado puede ser rojo),se llama a insertfix*/



     insertfix(z);
}

void RBtree::insertfix(node *z)
{
    cout<<z->key<<endl;
     node *u;

     while(z->parent!=nullptr && z->parent->color=='r'){
        if(z->parent==z->parent->parent->left){
            u=z->parent->parent->right;
            if( u!=nullptr && u->color=='r'){

                z->parent->color='b';
                u->color='b';
                z->parent->parent->color='r';
                z=z->parent->parent;
            }

            else if(z->parent->right==z){
                  z=z->parent;
                  leftrotate(z);
                }
            else{
                  z->parent->color='b';
                  z->parent->parent->color='r';
                  rightrotate(z->parent->parent);
            }
          }

        else{
            u=z->parent->parent->left;
            if( u!=nullptr && u->color=='r'){

                z->parent->color='b';
                u->color='b';
                z->parent->parent->color='r';
                z=z->parent->parent;
            }

            else if(z->parent->left==z){
                  z=z->parent;
                  rightrotate(z);
                }
            else{
                  z->parent->color='b';
                  z->parent->parent->color='r';
                  leftrotate(z->parent->parent);
            }

        }
     }
     root->color='b';
}


void RBtree::transplant(node *u,node*v){
      if(u->parent==nullptr){
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


      while(z!=nullptr)
      {
        if(z->key>clave){z=z->right;}
        else if(z->key<clave){z=z->left;}
        else{break;}

      }
      if(z==nullptr){return;}


      y=z;
      ycor=y->color;
      if(z->left==nullptr){
          x=z->right;
          transplant(z,z->right);
      }
      else if(z->right==nullptr){
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
      while(x->left!=nullptr){x=x->left;}
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
     if(y->left!=nullptr){y->left->parent=x;}
     y->parent=x->parent;
     if(x->parent==nullptr){root=y;}
     else{x->parent->right=y;}
     y->left=x;
     x->parent=y;



}
void RBtree::rightrotate(node *x)
{
     node *y=new node;
     y=x->left;
     x->left=y->right;
     if(y->right!=nullptr){y->right->parent=x;}
     y->parent=x->parent;
     if(x->parent==nullptr){root=y;}
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
     if(root==nullptr)
     {
          cout<<"\nARBOL VACIO.";
          return ;
     }
     if(p!=nullptr)
     {
                cout<<"\n\t NODO: ";
                cout<<"\n LLAVE: "<<p->key;
                cout<<"\n COLOR: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=nullptr)
                       cout<<"\n Padre: "<<p->parent->key;

                if(p->right!=nullptr)
                       cout<<"\n Hijo derecho: "<<p->right->key;
                else
                       cout<<"\n Este no tiene hijo derecho .  ";
                if(p->left!=nullptr)
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
/*
node *a=new node;
node *b=new node;
node *c=new node;
node *d=new node;
node *e=new node;
node *f=new node;
node *g=new node;
node *h=new node;
node *i=new node;

arbol.insert(a);
arbol.insert(b);
arbol.insert(c);
arbol.insert(d);
arbol.insert(e);
arbol.insert(f);
arbol.insert(g);
arbol.insert(h);
arbol.insert(i);


*/
//arbol.disp();
//arbol.del(7);
cout<<"**************************************"<<endl;
//arbol.disp();
//cout<<"**************************************"<<endl;

//arbol.del(2);




for(int i=1;i<=10;i++){
    arbol.insert(i);
}
arbol.disp();
//arbol.del(4);
cout<<"**************************************"<<endl;
//arbol.disp();







}
