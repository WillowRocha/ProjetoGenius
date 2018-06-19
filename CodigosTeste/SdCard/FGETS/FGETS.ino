void setup(){
  demoFgets();
}

void demoFgets() {
  char line[25];
  int n;
  // open test file
  SdFile file("FGETS.TXT", O_READ);
  
  // check for open error
  if (!file.isOpen()) error("demoFgets");

  // read lines from the file
  while ((n = file.fgets(line, sizeof(line))) > 0) {
    if (line[n - 1] == '\n') {
      // remove '\n'
      line[n-1] = 0;
      // replace next line with LCD call to display line
      Serial.println(line);
    } else {
      // no '\n' - line too long or missing '\n' at EOF
      // handle error
    }
  }
}
