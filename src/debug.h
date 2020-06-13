FILE *debug_file;

void debug_init() {
    debug_file = fopen("/home/shiro/tmp/debug-key-mods.txt", "w");
    if (debug_file != NULL) {
        fprintf(debug_file, "starting log session\n");
    } else {
        // do nothing
        //perror("fopen");
    }
}

void log(){

}
