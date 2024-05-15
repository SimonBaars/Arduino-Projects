enum http_methods{POST,GET,DELETE};

typedef struct {
String url;
http_methods method;
}RequestLine;
