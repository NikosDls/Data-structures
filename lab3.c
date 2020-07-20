/*
    date:24/01/2015
    purpose:sullogi vivlion me binary search trees kai singly linked lists.
    preconditions:ulopoihsi sunartiseon anazitisis, emfanhsis,apothikeusis,fortosis,dimiourgias kai diagrafis enos vivliou me apo8ikeusi olwn ton dedomenwn se binary search tree.
    postconditions:pragmatopoihsh sunartisewn kai sundesi tou binary search tree me singly linked list (enimerosi, fortosi k apo8ikeusi apo/se arxeio).  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Author //o kathe syggrafeas
{
    int author_id;
    char fname[50];
    char lname [50];
} Author;

typedef struct ListBookNode //o kombos ths listas
{
    int book_id;
    char title[50];
    char publisher [50];
    int numOfAuthors;
    Author authors[5];//statikos pinakas me tous syggrafeis
    struct ListBookNode* next;//pointer ston epomeno kombo
} ListBookNode;

typedef struct BookNode //o kombos toy BST
{
    int book_id;
    char title[50];
    char publisher [50];
    int numOfAuthors;
    Author authors[5];//statikos pinakas me tous syggrafeis
    struct BookNode* left;//aristero paidi
    struct BookNode* right;//deksi paidi
    struct ListBookNode* ListPointer;
//to pedio ListPointer einai enas deikths ston kombo ths listas ston opoio enai apothikeymana ta idia stoixeia gia to kathe biblio.
} BookNode;

//olh h plhroforia apothgikeyetai se mia struct me 2 pedia
//1: enas pointer sth riza enos BST
//2: ton arithmo twn bibliwn
typedef struct Books
{
    BookNode* root;
    int numOfBooks;
} Books;
typedef struct BooksBackUp
{
    ListBookNode* head;
    int numOfBooks;
} BooksBackUp;

void initialize(struct Books * bt);
void add_book(struct Books * bt,int data);
void printTree(BookNode *node);
void save_to_file(BookNode *node,FILE *fp);
void display_by_book_id(BookNode *node,int d);
void display_author_by_author_id(BookNode *node,int data);
void display_author_by_title(BookNode *node,char *title);
void display_books_by_surname(BookNode *node,char *name);
void load_from_file(Books *bt,BookNode *nn,FILE *fp);
BookNode* Delete(BookNode *root, int data);
BookNode* FindMin(BookNode* root);
void add_author(BookNode ** bt,int data);
void update(BookNode ** bt,ListBookNode **lbt,int count);
void display_books(ListBookNode *head,int books_count);
int copy_backup(char *filename);
int load_list(BooksBackUp *lbt);
int save_list(BooksBackUp lbt);
int main ()
{
    Books bt;
    BooksBackUp lbt;
    lbt.numOfBooks=0;
    lbt.head=NULL;
    initialize(&bt);
    FILE *fp;
    int choice,result=0,data=0;
    char *text1=(char*)malloc(15);//kanw malloc gia na desmeuesw xwro g ena string.
    char *text2=(char*)malloc(15);
    char *title=(char*)malloc(50);
    char *name=(char*)malloc(50);
    char *filename=(char*)malloc(15);
    text1[0]='0';//arxikopoiw tin arxi tou string se 0.
    text2[0]='0';

    do
    {
        do
        {
            printf("\n\n1.Load books from file. \n");
            printf("2.Save books to file. \n");
            printf("3.Update files. \n");
            printf("4.Display a book by id.\n");
            printf("5.Display an author by authors' id.\n");
            printf("6.Display the authors by title. \n");
            printf("7.Display books by authors' last name.\n");
            printf("8.Add a book.\n");
            printf("9.Add an author.\n");
            printf("10.Delete a book by id.\n");
            printf("11.Display all books and all authors.\n");
            printf("12.Update the list by BST.\n");
            printf("0.Exit.\n");

            printf("Choice : ");
            scanf("%d",&choice);
        }
        while(choice<0 || choice >12);
        switch(choice)
        {
        // load books from file
        case 1:
        {
            printf("Give the file of the name you want to load your data of the bst (and list).\n");
            fflush(stdin);
            scanf("%s",text1);
            fp=fopen(text1,"r");
            if(fp==NULL) return 0;
            fscanf(fp,"%d\n",&bt.numOfBooks);
            if(bt.root==0)
            load_from_file(&bt,bt.root,fp);
            else {free(bt.root);}
            fclose(fp);
            //printf("1o fclose done.\n");
            result =load_list(&lbt);
            if(result==1)
            printf(" Successful loading from file.\n");
            fclose(fp);
            //printf("2o fclose done.\n");
            break;
        }
        //save books to file.
        case 2:
        {
            printf(" Give the name of the file you want to save your data of the books(for bst and list).\n");
            scanf("%s",text1);
            fp=fopen(text1,"w");
            if (fp==NULL) return 0;
            fprintf(fp,"%d\n",bt.numOfBooks);
            save_to_file(bt.root,fp);
            fclose(fp);
            save_list(lbt);
            break;
        }
        //update file from list to file from bst
        case 3:
        {
            printf("Give the name of the file bst.\n");
            scanf("%s",filename);
            copy_backup(filename);
            break;
        }
        //display by book_id
        case 4:
        {
            printf("Give the id of the book you want. \n");
            fflush(stdin);
            scanf("%d",&data);
            printf("\n");
            printf("Number of Books : %d\n",bt.numOfBooks);
            display_by_book_id(bt.root,data);
            break;
        }
        //display author by author_id.
        case 5:
        {   printf("Give the id of the author you want. \n");
            fflush(stdin);
            scanf("%d",&data);
            printf("\n");
            printf("Number of Books : %d\n",bt.numOfBooks);
            display_author_by_author_id(bt.root,data);
            break;
        }
        //display authors by title.
        case 6:
        {   printf("Give the title of the book you want. \n");
            fflush(stdin);
            scanf("%s",title);
            printf("\n");
            printf("Number of Books : %d\n",bt.numOfBooks);
            display_author_by_title(bt.root,title);
            break;
        }
        //display all books written by one author(by last_name).
        case 7:
        {
            printf("Give the surname of the author. \n");
            fflush(stdin);
            scanf("%s",name);
            printf("\n");
            printf("Number of books : %d\n",bt.numOfBooks);
            display_books_by_surname(bt.root,name);
            break;
        }
        //add a book.
        case 8:
        {
            printf("Give the id of the book.\n");
            fflush(stdin);
            scanf("%d",&data);
            add_book(&bt,data);
            break;
        }
        //add an author.
        case 9:
        {
            printf("Give the id of the book.\n");
            fflush(stdin);
            scanf("%d",&data);
            add_author(&bt.root,data);
            break;
        }
        //delete a book.
        case 10:
        {
            printf("Give the id of the book.\n");
            fflush(stdin);
            scanf("%d",&data);
            Delete(bt.root,data);
            bt.numOfBooks--;
            break;
        }
        //display all books.
        case 11:
        {
            printf("Number of Books : %d\n",bt.numOfBooks);
            printTree(bt.root);
            break;
        }
        //update list by bst.
        case 12:
        {    update(&bt.root,&lbt.head,0);
             lbt.numOfBooks=bt.numOfBooks;
             display_books(lbt.head,bt.numOfBooks);
            break;
        }
        case 0:
        {
            printf("The program is about to exit");
            return 0;
            break;
        }
        }
    }
    while(1);

    return 0;
}
void initialize(struct Books * bt)//arxikopoihsh.
{
    bt->root=0;
    bt->numOfBooks=0;
}

void add_book(struct Books * bt,int data)
{
    struct BookNode * nn;
    int i;
    if(bt->numOfBooks==0)
    {
        bt->root= (struct BookNode*) malloc(sizeof(BookNode));
        printf("Give the title of the book.\n");
        fflush(stdin);
        scanf("%s",(bt->root)->title);
        //printf("%s",(bt->root)->title);
        printf("Give the publisher of the book: ");
        fflush(stdin);
        scanf("%s",(bt->root)->publisher);
       // printf("%s",(bt->root)->publisher);
        printf("Give the number of the authors: ");
        fflush(stdin);
        scanf("%d",&(bt->root)->numOfAuthors);
        //printf("%d",(bt->root)->numOfAuthors);
        for(i=0; i <(bt->root)->numOfAuthors; i++)
        {
            printf("Give the author_id  :\n");
            fflush(stdin);
            scanf("%d",&(bt->root)->authors[i].author_id);
           // printf("%d",(bt->root)->authors[i].author_id);
            printf("Give the first name of the author  :\n");
            fflush(stdin);
            scanf("%s",(bt->root)->authors[i].fname);
            //printf("%s",(bt->root)->authors[i].fname);
            printf("Give the last name of the author  :\n");
            fflush(stdin);
            scanf("%s",(bt->root)->authors[i].lname);
            //printf("%s",(bt->root)->authors[i].lname);
        }
        (bt->root)->book_id=data;
        (bt->root)->left=0;
        (bt->root)->right=0;
        bt->numOfBooks++;
        bt->root->ListPointer=0;
    }
    else
    {
        nn=(bt->root);

        while (nn !=0  && nn->book_id!=data)
        {
            if(nn->book_id<data)  //turn right
            {
                if (nn->right==0) //create new node
                {
                    nn->right= (struct BookNode*) malloc(sizeof(BookNode));
                    printf("Give the title of the book.\n");
                    fflush(stdin);
                    scanf("%s",(nn->right)->title);
                    //printf("%s",(nn->right)->title);
                    printf("Give the publisher of the book: ");
                    fflush(stdin);
                    scanf("%s",(nn->right)->publisher);
                    //printf("%s",(nn->right)->publisher);
                    printf("Give the number of the authors: ");
                    fflush(stdin);
                    scanf("%d",&(nn->right)->numOfAuthors);
                    //printf("%d",(nn->right)->numOfAuthors);
                    for(i=0; i <(nn->right)->numOfAuthors; i++)
                    {
                        printf("Give the author_id  :\n");
                        fflush(stdin);
                        scanf("%d",&(nn->right)->authors[i].author_id);
                        //printf("%d",(nn->right)->authors[i].author_id);
                        printf("Give the first name of the author  :\n");
                        fflush(stdin);
                        scanf("%s",(nn->right)->authors[i].fname);
                        //printf("%s",(nn->right)->authors[i].fname);
                        printf("Give the last name of the author  :\n");
                        fflush(stdin);
                        scanf("%s",(nn->right)->authors[i].lname);
                        //printf("%s",(nn->right)->authors[i].lname);
                    }
                    (nn->right)->left=0;
                    (nn->right)->right=0;
                    (nn->right)->book_id=data;
                    bt->numOfBooks++;
                    bt->root->ListPointer=0;
                    return;
                }
                else   //follow right
                {
                    nn=nn->right;
                }
            }
            else   //turn left
            {
                if (nn->left==0) //create new node
                {
                    nn->left= (struct BookNode*) malloc(1*sizeof(BookNode));
                    printf("Give the title of the book.\n");
                    fflush(stdin);
                    scanf("%s",(nn->left)->title);
                    //printf("%s",(nn->left)->title);
                    printf("Give the publisher of the book: ");
                    fflush(stdin);
                    scanf("%s",(nn->left)->publisher);
                    //printf("%s",(nn->left)->publisher);
                    printf("Give the number of the authors: ");
                    fflush(stdin);
                    scanf("%d",&(nn->left)->numOfAuthors);
                    //printf("%d",(nn->left)->numOfAuthors);
                    for(i=0; i <(nn->left)->numOfAuthors; i++)
                    {
                        printf("Give the author_id  :\n");
                        fflush(stdin);
                        scanf("%d",&(nn->left)->authors[i].author_id);
                        //printf("%d",(nn->left)->authors[i].author_id);
                        printf("Give the first name of the author  :\n");
                        fflush(stdin);
                        scanf("%s",(nn->left)->authors[i].fname);
                        //printf("%s",(nn->left)->authors[i].fname);
                        printf("Give the last name of the author  :\n");
                        fflush(stdin);
                        scanf("%s",(nn->left)->authors[i].lname);
                        //printf("%s",(nn->left)->authors[i].lname);
                    }
                    (nn->left)->left=0;
                    (nn->left)->right=0;
                    (nn->left)->book_id=data;
                    bt->numOfBooks++;
                    bt->root->ListPointer=0;
                    return;
                }
                else   //follow left
                {
                    nn=nn->left;
                }
            }
        }
    }
}


void add_author(BookNode ** bt,int data)
{
    int i,num;

    if((*bt)->book_id == data){
        num=(*bt)->numOfAuthors;
        num++;
        (*bt)->numOfAuthors=num;
        printf("Enter the id of the author \n");
        //printf("number of the author %s\n", (*bt)->numOfAuthors);
        fflush(stdin);
        scanf("%d", &(*bt)->authors[(*bt)->numOfAuthors-1].author_id);
        printf("id of the author %d\n", (*bt)->authors[(*bt)->numOfAuthors-1].author_id);
        printf("Enter the name of the author \n");
        fflush(stdin);
        scanf("%s",(*bt)->authors[(*bt)->numOfAuthors-1].fname);
        printf("name of the author %s\n", (*bt)->authors[(*bt)->numOfAuthors-1].fname);
        printf("Enter the last name of the author \n");
        fflush(stdin);
        scanf("%s",(*bt)->authors[(*bt)->numOfAuthors-1].lname);
        printf("last name of the author %s\n", (*bt)->authors[(*bt)->numOfAuthors-1].lname);
        printf("number of the authors %d\n", (*bt)->numOfAuthors);

        return;

    }
    if((*bt)->book_id < data)
    add_author(&(*bt)->right,data);
    if((*bt)->book_id > data)
    add_author(&(*bt)->left,data);

}

void printTree(BookNode *node)
{
    int i;
    if (node!=0)
    {

        printf("Books'ID : %d\n",node->book_id);
        printf("Title : %s\n",node->title);
        printf("Publisher : %s\n", node->publisher);
        printf("Number of authors : %d\n",node->numOfAuthors);
        for(i=0; i<node->numOfAuthors; i++)
        {
            printf("Authors'ID %d\n",node->authors[i].author_id);
            printf("Name %s\n",node->authors[i].fname);
            printf("Last name %s\n",node->authors[i].lname);
        }
        printTree(node->left);
        printTree(node->right);
    }
}

void save_to_file(BookNode *node,FILE *fp)
{
    int i;
    if (node!=0)
    {
        fprintf(fp,"%d\n",node->book_id);
        fprintf(fp,"%s\n",node->title);
        fprintf(fp,"%s\n", node->publisher);
        fprintf(fp,"%d\n",node->numOfAuthors);
        for(i=0; i<node->numOfAuthors; i++)
        {
            fprintf(fp,"%d\n",node->authors[i].author_id);
            fprintf(fp,"%s\n",node->authors[i].fname);
            fprintf(fp,"%s\n",node->authors[i].lname);
        }
        save_to_file(node->left,fp);
        save_to_file(node->right,fp);
    }

}

void display_by_book_id(BookNode *node,int data)//euresh stoixeion vivliou bash book_id.
{
    int i;
    if (node!=0)
    {
        if(node->book_id==data)
        {
            printf("Books'ID : %d\n",node->book_id);
            printf("Title : %s\n",node->title);
            printf("Publisher : %s\n", node->publisher);
            printf("Number of authors : %d\n",node->numOfAuthors);
            for(i=0; i<node->numOfAuthors; i++)
            {
                printf("Authors'ID %d\n",node->authors[i].author_id);
                printf("Name %s\n",node->authors[i].fname);
                printf("Last name %s\n",node->authors[i].lname);
            }
            // return;
        }
        //else printf("The book with this id was not found.\n");
        if(node->book_id>data)
            display_by_book_id(node->left,data);

        if(node->book_id<data)
            display_by_book_id(node->right,data);
    }
    else printf("The display of the books id wasnt successful.\n");

}
void display_author_by_author_id(BookNode *node,int data)//emfanish stoixeion suggrafea vash author_id.
{
    int i,j;
    if (node!=0)
    {
            for(i=0; i<node->numOfAuthors; i++)
            {
                if(node->authors[i].author_id==data)
                    {

                    printf("Authors'ID %d\n",node->authors[i].author_id);
                    printf("Name %s\n",node->authors[i].fname);
                    printf("Last name %s\n",node->authors[i].lname);
                    }
            // return;
        }
            display_author_by_author_id(node->left,data);
            display_author_by_author_id(node->right,data);
    }

}


void display_author_by_title(BookNode *node,char *title)
{
    int i;
    if (node!=0)
    {       if(strcmp(node->title,title)==0)
            {
                    for(i=0; i<node->numOfAuthors; i++)
                    {
                    printf("Authors'ID %d\n",node->authors[i].author_id);
                    printf("Name %s\n",node->authors[i].fname);
                    printf("Last name %s\n",node->authors[i].lname);
                    }
            // return;
        }

            display_author_by_title(node->left,title);
            display_author_by_title(node->right,title);
    }

}

void display_books_by_surname(BookNode *node,char *name)
{
    int i,j;
    if (node!=0)
    {       for(i=0; i<node->numOfAuthors; i++)
                {
                if(strcmp(node->authors[i].lname,name)==0){
                    printf("Books'ID : %d\n",node->book_id);
                    printf("Title : %s\n",node->title);
                    printf("Publisher : %s\n", node->publisher);
                    printf("Number of Authors : %d\n",node->numOfAuthors);
                        for(j=0; j<node->numOfAuthors; j++)
                        {
                            printf("Authors'ID %d\n",node->authors[j].author_id);
                            printf("Name %s\n",node->authors[j].fname);
                            printf("Last name %s\n",node->authors[j].lname);
                        }
                        break;
                }
        }

            display_books_by_surname(node->left,name);
            display_books_by_surname(node->right,name);
    }
    //else printf("The display of the books by authors' last name wasnt successful.\n");

}
void load_from_file(Books *bt,BookNode *nn,FILE *fp)
{
    int i;
    if(bt->numOfBooks==1 || bt->root == 0)
    {
        bt->root= (BookNode*) malloc(sizeof(BookNode));
        fscanf(fp,"%d",&(bt->root)->book_id);
        //printf("Book id : %d \n", bt->root->book_id);
        fflush(stdin);
        fscanf(fp,"%s",(bt->root)->title);
        fflush(stdin);
        fscanf(fp,"%s",(bt->root)->publisher);
        fflush(stdin);
        fscanf(fp,"%d",&(bt->root)->numOfAuthors);
        for(i=0; i <(bt->root)->numOfAuthors; i++)
        {
            fflush(stdin);
            fscanf(fp,"%d",&(bt->root)->authors[i].author_id);
            fflush(stdin);
            fscanf(fp,"%s",(bt->root)->authors[i].fname);
            fflush(stdin);
            fscanf(fp,"%s",(bt->root)->authors[i].lname);
        }
        //(bt->root)->book_id=data;
        (bt->root)->left=0;
        (bt->root)->right=0;
       // bt->numOfBooks++;
        bt->root->ListPointer=0;
    }
        else
    {
        nn = (bt->root);

        BookNode *nn2 = (BookNode*)malloc(sizeof(BookNode));

                    fflush(stdin);
                    fscanf(fp,"%d",&nn2->book_id);
                    //printf("Book id 1: %d\n", nn2->book_id);
                    //printf("Book id 2: %d\n", (bt->root)->book_id);
                    fflush(stdin);

                    fscanf(fp,"%s",nn2->title);
                    //printf("%s",(nn->right)->title);
                    fflush(stdin);
                    fscanf(fp,"%s",nn2->publisher);
                    //printf("%s",(nn->right)->publisher);
                    fflush(stdin);
                    fscanf(fp,"%d",&nn2->numOfAuthors);
                    //printf("%d",(nn->right)->numOfAuthors);
                    for(i=0; i <nn2->numOfAuthors; i++)
                    {
                        fflush(stdin);
                        fscanf(fp,"%d",&nn2->authors[i].author_id);
                        //printf("%d",(nn->right)->authors[i].author_id);
                        fflush(stdin);
                        fscanf(fp,"%s",nn2->authors[i].fname);
                        //printf("%s",(nn->right)->authors[i].fname);
                        fflush(stdin);
                        fscanf(fp,"%s",nn2->authors[i].lname);
                        //printf("%s",(nn->right)->authors[i].lname);
                    }


        while (nn != 0  && nn->book_id!=nn2->book_id)
        {

            if(nn->book_id<nn2->book_id)  //turn right
            {

                if (nn->right==0) //create new node
                {

                    nn->right = nn2;

                    (nn->right)->left=0;
                    (nn->right)->right=0;
                    bt->root->ListPointer=0;
                    return;
                }
                else   //follow right
                {

                    nn=nn->right;
                }
            }
            else   //turn left
            {

                if (nn->left==0) //create new node
                {

                    nn->left = nn2;
                    (nn->left)->left=0;
                    (nn->left)->right=0;
                    bt->root->ListPointer=0;
                    return;
                }
                else   //follow left
                {

                    nn=nn->left;
                }
            }
        }
    }
    load_from_file(bt,(bt->root)->right,fp);
    load_from_file(bt,(bt->root)->left,fp);
}


 BookNode* Delete(BookNode *root, int data) {
	if(root == NULL) return root;
	else if(data < root->book_id) root->left = Delete(root->left,data);
	else if (data > root->book_id) root->right = Delete(root->right,data);
	else {
		// Case 1:  No child
		if(root->left == NULL && root->right == NULL) {
			free(root) ;
			root = NULL;
		}
		//Case 2: One child
		else if(root->left == NULL) {
			struct BookNode *temp = root;
			root = root->right;
			free(temp);
		}
		else if(root->right == NULL) {
			struct BookNode *temp = root;
			root = root->left;
			free(temp);
		}
		// case 3: 2 children
		else {
			struct BookNode *temp = FindMin(root->right);
			root->book_id = temp->book_id;
			root->right = Delete(root->right,temp->book_id);
		}
	}
	return root;
}

BookNode* FindMin(BookNode* root)
{

	while(root->left != NULL) root = root->left;
	return root;
}


void update(BookNode ** bt,ListBookNode **lbt,int count){
    int i;
    if(!(*bt))
        return;
    ListBookNode *nlbt=(struct ListBookNode*)malloc(sizeof(ListBookNode));
    ListBookNode *cur=NULL;
    nlbt->book_id=(*bt)->book_id;
    strcpy(nlbt->title,(*bt)->title);
    strcpy(nlbt->publisher,(*bt)->publisher);
    nlbt->numOfAuthors=(*bt)->numOfAuthors;
    for(i=0; i < (*bt)->numOfAuthors; i++){
        nlbt->authors[i].author_id= (*bt)->authors[i].author_id;
        strcpy(nlbt->authors[i].fname, (*bt)->authors[i].fname);
        strcpy(nlbt->authors[i].lname, (*bt)->authors[i].lname);
    }
    (*bt)->ListPointer=nlbt;
    if(count==0){
        (*lbt)=nlbt;
        count++;
       // return;
    }else{
    cur=(*lbt);
    while(cur->next!=NULL){
    cur=cur->next;
     printf("\n");
    }
    cur->next=nlbt;
    }
    update(&(*bt)->right,&(*lbt),count);
    update(&(*bt)->left,&(*lbt),count);
}

void display_books(ListBookNode *head,int books_count){
int i;
ListBookNode *cur=head;

printf("Number of the Books =%d\n",books_count);
printf("\n");
if(head==NULL){
    printf("The list is empty.\n");
    return;
}
while(cur!=NULL){

printf("Id: %d\n Title: %s\n Publisher:%s\n Number Of Authors: %d\n ",cur->book_id,cur->title,cur->publisher,cur->numOfAuthors);
    for(i=0; i <cur->numOfAuthors; i++){
        printf("Author's id: %d\n",cur->authors[i].author_id);
        printf("Author's first name: %s\n",cur->authors[i].fname);
        printf("Author's last name: %s\n",cur->authors[i].lname);

    }
    cur=cur->next;
}
printf("The display was successful.\n");
}

int copy_backup(char * filename)
{
FILE*fp1,*fp2;
size_t n, m;
unsigned char buff[8192];
fp1 = fopen(filename,"r");
if(fp1 == NULL)
{
    printf("error fp1.\n");
            return -1;
}
fp2 = fopen("test1.txt","w");//dimiourgei kainourio arxeio.
if(fp2 == NULL)
{
    printf("Error2 fp2.\n");
    return -1;
}

do
{
n = fread(buff, 1, sizeof buff, fp1);
if (n)
m = fwrite(buff, 1, n, fp2);
else // se periptwsi la8ous.
m = 0;
}
while ((n > 0) && (n == m));//oso to mege8os tou arxeiou einai >0 k einai iso me to mege8os tu dimiourgoumenou.

if (m) printf("Error copy.\n");
fclose(fp1);
fclose(fp2);
return 0;
}

int save_list(BooksBackUp lbt){

int j;
ListBookNode *cur=lbt.head;
    FILE *fp;
    fp=fopen("test1.txt","w");
    if (fp==NULL) return 0;
    fprintf(fp,"%d\n",lbt.numOfBooks);
    while(cur!=NULL){

        fprintf(fp,"%d\n%s\n%s\n%d\n",cur->book_id,cur->title,cur->publisher,cur->numOfAuthors);

       for(j=0; j <cur->numOfAuthors; j++) {

        fprintf(fp,"%d\n%s\n%s\n",cur->authors[j].author_id,cur->authors[j].fname,cur->authors[j].lname);
            }
        cur=cur->next;
    }
    fclose(fp);
    printf("Successful saving.\n");
    return 1;

}

int load_list(BooksBackUp *lbt){
int count=1;

FILE *fp;
int i,j,temp;
ListBookNode *cur=NULL;
fp=fopen("test1.txt","r");
            if (fp==NULL) {
           // printf("Error opening the file.\n");
            return 0;
            }


else {
        lbt->head=(ListBookNode*)malloc(sizeof(ListBookNode));
        fscanf(fp,"%d",&lbt->numOfBooks);


            fflush(stdin);
            fscanf(fp,"%d %s %s %d",&lbt->head->book_id,lbt->head->title,lbt->head->publisher,&lbt->head->numOfAuthors);
            //printf("Id :%d\n Title : %s\n Publisher: %s\n Number of authors :%d\n",lbt->head->book_id,lbt->head->title,lbt->head->publisher,lbt->head->numOfAuthors);

                for(i=0; i <lbt->head->numOfAuthors; i++){
                    fflush(stdin);
                    fscanf(fp,"%d %s %s",&lbt->head->authors[i].author_id,lbt->head->authors[i].fname,lbt->head->authors[i].lname);
                     //printf("Author's id :%d\n Author's First Name :%s\n Author's Last Name:%s\n",lbt->head->authors[i].author_id,lbt->head->authors[i].fname,lbt->head->authors[i].lname);

                }


        cur=lbt->head;

        while(!feof(fp) && count<lbt->numOfBooks){
            cur->next=(ListBookNode*)malloc(sizeof(ListBookNode));
            cur = cur->next;
            fflush(stdin);

            fscanf(fp,"%d %s %s %d",&cur->book_id,cur->title,cur->publisher,&cur->numOfAuthors);
           // printf("Id :%d\n Title : %s\n Publisher: %s\n Number of authors :%d\n",cur->book_id,cur->title,cur->publisher,cur->numOfAuthors);

                for(i=0; i <cur->numOfAuthors; i++){
                     fflush(stdin);
                    fscanf(fp,"%d %s %s",&cur->authors[i].author_id,cur->authors[i].fname,cur->authors[i].lname);
                   // printf("Author's id :%d\n Author's First Name :%s\n Author's Last Name:%s\n",cur->authors[i].author_id,cur->authors[i].fname,cur->authors[i].lname);

                }

            count++;
        }
        cur->next=NULL;
}

}


