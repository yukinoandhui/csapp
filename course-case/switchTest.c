void switcher(long x){
    int a=1;
    switch(x){
        case 1:
          a+=1;
          break;
        case 2:
          a+=3;
          break;
        case 3:
          a+=3;
          break;
        case 4:
          a+=4;
          break;
        case 5:
        case 6:
          a+=6;
          break;
        case 9:
          a+=333;
          x-=1;
          break;
        case 10:
          a+=444;
          break;
        default:
          a=1233;
          break;
    }
}
