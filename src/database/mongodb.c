#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mongoc/mongoc.h>
// #include <mongoc/mongo-init.c>
// #include <libbson/bson.h>

const char *uri_string = "mongodb+srv://doadmin:QCZ5U26n479qEB01@stack-exchange-mongodb-94b08e11.mongo.ondigitalocean.com/admin?tls=true&authSource=admin&replicaSet=stack-exchange-mongodb";




int main(int argc, char const *argv[])
{
    mongoc_uri_t *uri;
    mongoc_client_t *client;
    bson_t *command, reply;
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

    mongoc_client_set_appname(client, "StackExchange-Demake");

    command = BCON_NEW("ping", BCON_INT32(1));

    inval_arg = mongoc_client_command_simple(client, "admin", command, NULL, &reply, &error);

    if(!inval_arg)
    {
        fprintf(stderr, "%s\n", error.message);
        return EXIT_FAILURE;
    }

    response = bson_as_json(&reply, NULL);
    printf("%s\n", response);


    bson_destroy(&reply);
    bson_destroy(command);
    bson_free(response);

    mongoc_uri_destroy(uri);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return EXIT_SUCCESS;
}