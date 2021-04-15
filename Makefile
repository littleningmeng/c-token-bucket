TARGET=test
$(TARGET):
	gcc main.c token_bucket.c -lpthread -o $@
clean:
	rm -f $(TARGET)
