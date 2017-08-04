//---------------------------------------------------------------------------

#ifndef rulegetH
#define rulegetH




double fgauss(double u, double b, double c);                     //фн. Гаусса
int gauss(double u, double c);                                             //u - процент беых пикселей. вычисляет принадлежности фн. Гаусса и возвращает зн. id=[0;4] для правила
double gaussFZ(double u); //for fuzzy
void getrule(int rmas[1000][100]);                               //2 считываение базы правил в массив
void getid(int rmas[1000][100], int imas[1000], int tmas[50][50]); //4 определение цифры на основании getrule и getnum
void getidT(int rmas[1000][100], int imas[1000], int tmas[50][50]);
int getidF(int rmas[1000][100], int imas[1000], double ifmas[1000][10]); //for fuzzy
void getnum(int imas[1000], int wglob, int hglob, int sCl);               //3 генерация правила для определяемой цифры по квадратичной ФП
void getnumgauss(TImage* AImage, int imas[1000], int wglob, int hglob, int sCl, double c);          //3 генерация правила для определяемой цифры по Гауссовой ФП
void getnumgauss37(TImage* AImage, int imas[1000], double ifmas[1000][10], int wglob, int hglob, int sCl, double c);
void fpgauss(int wglob, int hglob);                              //генерация правил по ФП Гаусса
void fpgauss37(int wglob, int hglob); 
void printid(TEdit* AEdit, int tmas[50][50]);
void printidF(TEdit* AEdit, int idp); //for fuzzy
void SetMemo(TEdit* AEdit, TMemo* AMemo); //Memo output

//---------------------------------------------------------------------------
#endif
