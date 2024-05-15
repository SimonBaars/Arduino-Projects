void heffenOmlaag() {
  for (int i=0;i<90;i++) {
    hefboom.write(i);
    delay(50);
  }
}

void heffenOmhoog() {
  hefboom.write(0);
}



