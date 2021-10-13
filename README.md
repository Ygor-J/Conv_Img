##### Como requerido pelo Professor Lehilton Pedrosa do IC, alunos da UNICAMP estão expressamente proibidos de copiar ou modificar qualquer trecho deste código para uso em suas disciplinas e tarefas. Especialmente, não é permitido utilizá-lo nas disciplinas MC102 e MC202. Se precisam de ajudam com suas tarefas, procurem monitores ou peçam ajuda ao respectivo professor.
##### As requested by Professor Lehilton from the Institute of Computing, UNICAMP students are not allowed to copy or modify any part of this code for use on academic disciplines. Especially, MC102 and MC202. If you need help, ask your professors or upperclasmen.

Just playing around with convolution/kernels and Netpbm file formats. Only able to apply convolution to the Portable Pixmap Format (PPM), otherwise known by its magic number P3 or P6 for binary.  
Support only for 3x3 kernels so far.  

Img - No Filter  
![Img - No Filter](https://github.com/Ygor-J/Conv_Img/blob/master/tests/bike.png)  
Img - Emboss Filter  
![Img - Emboss Filter](https://github.com/Ygor-J/Conv_Img/blob/master/img.png)

```
emboss_filter = [
     [-2, -1, 0],
     [-1, 1, 1],
     [0, 1, 2]
  ]
```
