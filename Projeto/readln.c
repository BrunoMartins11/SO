char* readln(int fildes, size_t* nbyte){
        int n=0;
        ssize_t r;
        char* buf;// aloc
        r = read(fildes, buf, 1);
        if(0 == strncmp(buf,">>>",3))
        	while(r > 0 && n < (nbyte-1) && 0 != strncmp(buf,"<<<",3)){
        		n++;
        		r = read(fildes, &buf[n], 1);
			}
       		else {
       			while(r > 0 &&  buf[n]!="\n" && buf[n]!="\0" && buf[0]!=EOF && n<(nbyte-1)){
        			n++;
        			r = read(fildes, &buf[n], 1);
			}
   	   }

       return buf;

}
