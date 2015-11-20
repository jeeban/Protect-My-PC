
#!/bin/bash
gcc -Wall -Wextra alm_gui_mode.c -o alm_gui `pkg-config --libs --cflags gtk+-2.0` > /dev/null 2>&1
gcc -Wall -Wextra alm_cli_mode.c -o alm_cli `pkg-config --libs --cflags gtk+-2.0` > /dev/null 2>&1
gcc -Wall -Wextra alm_interface.c -o alm_interface `pkg-config --libs --cflags gtk+-2.0` > /dev/null 2>&1
gcc -Wall -Wextra alm_run.c -o alm-run > /dev/null 2>&1
#rm alm_gui_mode.c alm_cli_mode.c alm_interface.c alm_run.c
if [ ! -f alm_gui ]
then
	echo 1
	exit 0
fi
mv alm_gui /home/`whoami`/.alm/scripts
mv alm_cli /home/`whoami`/.alm/scripts
mv alm_interface /home/`whoami`/.alm/scripts
mv alm.desktop /home/`whoami`/.config/autostart
file=$(grep  "shopt -q login_shell &&  /bin/alm-run cli || : " /home/`whoami`/.bashrc | wc -l)
if [ $file -eq 0 ]
then
	echo "shopt -q login_shell &&  /bin/alm-run cli || : " >> /home/`whoami`/.bashrc
fi
#gksu cp alm-run /bin
echo 0
#rm manage_files.sh
exit 0