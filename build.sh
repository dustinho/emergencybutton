gcc -c emergencybutton.c hid.c
g++ main.cpp emergencybutton.o hid.o -framework IOKit -framework CoreFoundation -o serious_business

