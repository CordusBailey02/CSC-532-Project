#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mongoc/mongoc.h>
// #include <mongoc/mongo-init.c>
// #include <libbson/bson.h>

const char *uri_string = "mongodb+srv://doadmin:QCZ5U26n479qEB01@stack-exchange-mongodb-94b08e11.mongo.ondigitalocean.com/admin?tls=true&authSource=admin&replicaSet=stack-exchange-mongodb";


mongoc_uri_t *uri;
mongoc_client_t *client;
bson_t *command, reply;


int connection_init()
{
    bson_error_t error;
    char *response;
    bool inval_arg;

    // initialize library internals
    mongoc_init();

    uri = mongoc_uri_new_with_error(uri_string, &error);
    
    if(!uri)
    {
        fprintf(stderr
                ,'failed to parse URI:  %s\n'
                ,'Error msg:            %s\n'
                ,uri_string
                ,error.message);
        return EXIT_FAILURE;
    }

    client = mongoc_client_new_from_uri(uri);
    if(!client)
    {
        return EXIT_FAILURE;
    }

    mongoc_client_set_appname(client, "connect-example");

    command = BCON_NEW("ping", BCON_INT32(1));

    inval_arg = mongoc_client_command_simple(client, "admin", command, NULL, &reply, &error);

    if(!inval_arg)
    {
        fprintf(stderr, "%s\n", error.message);
        return EXIT_FAILURE;
    }

    response = bson_as_json(&reply, NULL);
    printf("%s\n", response);


}


int write_to_mongo(char *data[])
{
    bson_t *document;
    int failure = EXIT_FAILURE;
    int time_out = 10;
    struct timespec ts;
    ts.tv_nsec = (10 % 1000) * 1000000;


    while(failure & time_out)
    {
        failure = connection_init();
        time_out = time_out - 1;
        nanosleep(&ts, NULL);
    }
     
    if(failure)
    {
        return EXIT_FAILURE;
    }

    collection = mongoc_client_get_collection(client, "posts", collection_name);

    document = BCON_NEW(
        "user", BCON_UTF8(data[0])
        ,"question", BCON_UTF8(data[1])
        ,"upvotes", BCON_INT32(data[2])
        ,"downvotes", BCON_INT32(data[3])
        ,"answers", "{"
                "userID", "{"
                        ,"answer", "No answer has been provided yet."
                        ,"upvotes", BCON_INT32(0)
                        ,"downvotes", BCON_INT32(0)
                ,"}"
        ,"}"

    )

    if(!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error))
    {
        fprint(stderr, "%s\n", error.message);
    }
    else
    {
        str = bson_as_canonical_exteded_jeson(doc, NULL);
        bson_free(str);
    }

    mongoc_collection_destroy(collection);
    mongoc_uri_destroy(uri);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return EXIT_SUCCESS;

}




int main(int argc, char const *argv[])
{

    bson_destroy(&reply);
    bson_destroy(command);
    bson_free(response);

    mongoc_uri_destroy(uri);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return EXIT_SUCCESS;
}