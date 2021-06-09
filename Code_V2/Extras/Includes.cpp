#include "../Headers.h"
#include "../Parser/Existe.cpp"
#include "../Parser/Ingresar.cpp"
#include "../Parser/Verificar.cpp"

#include "../Comandos/Cat.cpp"
#include "../Comandos/Chgrp.cpp"
#include "../Comandos/Chmod.cpp"
#include "../Comandos/Chown.cpp"
#include "../Comandos/Cp.cpp"
#include "../Comandos/Edit.cpp"
#include "../Comandos/Exec.cpp"
#include "../Comandos/Fdisk.cpp"
#include "../Comandos/Find.cpp"
#include "../Comandos/Login.cpp"
#include "../Comandos/Logout.cpp"
#include "../Comandos/Mkdir.cpp"
#include "../Comandos/Mkdisk.cpp"
#include "../Comandos/Mkfile.cpp"
#include "../Comandos/Mkfs.cpp"
#include "../Comandos/Mkgrp.cpp"
#include "../Comandos/Mkusr.cpp"
#include "../Comandos/Mount.cpp"
#include "../Comandos/Mv.cpp"
#include "../Comandos/Pause.cpp"
#include "../Comandos/Rem.cpp"
#include "../Comandos/Ren.cpp"
#include "../Comandos/Rep.cpp"
#include "../Comandos/Rmdisk.cpp"
#include "../Comandos/Rmgrp.cpp"
#include "../Comandos/Rmusr.cpp"
#include "../Comandos/Unmount.cpp"

Cat_ cat_;
Chgrp_ chgrp_;
Chmod_ chmod_;
Chown_ chown_;
Cp_ cp_;
Edit_ edit_;
Exec_ exec_;
Fdisk_ fdisk_;
Find_ find_;
Login_ login_;
Logout_ logout_;
Mkdir_ mkdir_;
Mkdisk_ mkdisk_;
Mkfile_ mkfile_;
Mkfs_ mkfs_;
Mkgrp_ mkgrp_;
Mkusr_ mkusr_;
Mount_ mount_;
Mv_ mv_;
Pause_ pause_;
Rem_ rem_;
Ren_ ren_;
Rep_ rep_;
Rmdisk_ rmdisk_;
Rmgrp_ rmgrp_;
Rmusr_ rmusr_;
Unmount_ unmount_;