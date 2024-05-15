enum http_methods{POST,GET,DELETE};

typedef struct {
  String *request;
  byte arraySize;
} RequestLine;
