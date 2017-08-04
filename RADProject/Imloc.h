//---------------------------------------------------------------------------

#ifndef ImlocH
#define ImlocH



void location(int& wglob, int& hglob, int sCl);                           //1 выделение цифры из изображения
void grayim(TImage* AImage);                                                   //преобразование цветного изображения в ч\б
void multiloc(TImage* AImage, TImage* BImage, int& vpixe, int& vmax, int& lwglob, int& lhglob, int& wglob, int& hglob, bool& cid2, int sCl); //1 выделение нескольких из изображения
int filpix(TImage* AImage); //median filter
//---------------------------------------------------------------------------
#endif
