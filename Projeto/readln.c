ssize_t readln(int fildes, void *buff, size_t nbyte){
        int n=0;
        ssize_t r;
        char* buf = buff;
        r = read(fildes, &buf[n], 1);
        while(r > 0 &&  buf[n]!="\n" && buf[n]!="\0" && buf[0]!=EOF && n<(nbyte-1)){
        n++;
        r = read(fildes, &buf[n], 1);

       }

       return n+1;

}
