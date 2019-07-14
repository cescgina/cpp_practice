int main(){
    // Without writing
    // bad_alloc with 20.000.000.000
    // bad_alloc with 4.000.000.000
    // bad_alloc with 3.000.000.000
    // bad_alloc with 2.500.000.000
    // bad_alloc with 2.250.000.000
    // bad_alloc with 2.150.000.000
    // bad_alloc with 2.130.000.000
    // Writing
    //
    int *a = new int[2000000000];
    for (int i=0; i < 2000000000; i++){
        a[i] = 0;
    }
}
