void setup() {
  size(768, 1024);
}

void draw() {
  String []data = loadStrings("http://106.187.54.242/upload/dar1203.txt");
  printArray(data);
  if (data[0].indexOf("1")>-1) {
    fill(255, 0, 0);
  } else {
    fill(0, 255, 0);
  }

  rect(random(width), random(width), random(width), random(height));
}
