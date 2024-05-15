enum http_methods{POST,GET,DELETE};

typedef struct {
  http_methods method;
  String path;
} RequestLine;
