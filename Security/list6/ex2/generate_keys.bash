openssl req -newkey rsa:2048 -keyout key.rsa -out csr_file.csr
openssl rsa -in key.rsa -pubout > rsa_pub.rsa
