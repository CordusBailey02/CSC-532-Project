#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mongoc/mongoc.h>
// #include <mongoc/mongo-init.c>
#include <libbson/bson.h>

const char *uri_string = "mongodb+srv://doadmin:QCZ5U26n479qEB01@stack-exchange-mongodb-94b08e11.mongo.ondigitalocean.com/admin?tls=true&authSource=admin&replicaSet=stack-exchange-mongodb";


mongoc_uri_t *uri;
mongoc_client_t *client;



void cleanup_mongo()
{
    mongoc_uri_destroy(uri);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    printf("\nCleanup Sucessfull...\n");
}


int connection_init()
{
    bson_error_t error;
    bson_t *command, reply;
    char *response;
    bool inval_arg;
    char *str;

    // initialize library internals
    mongoc_init();

    uri = mongoc_uri_new_with_error(uri_string, &error);
    
    if(!uri)
    {
        fprintf(stderr
                ,"failed to parse URI:  %s\n"
                 "Error msg:            %s\n"
                ,uri_string
                ,error.message);
        return EXIT_FAILURE;
    }

    printf("\nURI Success\n");

    client = mongoc_client_new_from_uri(uri);
    if(!client)
    {
        printf("Client Failure\n");
        return EXIT_FAILURE;
    }

    printf("\nClient Success\n");

    // mongoc_client_set_appname(client, "stack-exchange-mongodb");

    command = BCON_NEW("ping", BCON_INT32(1));

    inval_arg = mongoc_client_command_simple(client, "admin", command, NULL, &reply, &error);

    if(!inval_arg)
    {
        printf("Errors in inval_arg");
        fprintf(stderr, "%s\n", error.message);
        return EXIT_FAILURE;
    }
    str = bson_as_json(&reply, NULL);
    // printf("%s\n", str);

    printf("\nClient-Command Success\n");

    bson_destroy(&reply);
    bson_destroy(command);
    bson_free(str);

    return EXIT_SUCCESS;

}


int write_to_mongo(char *username, char *question)
{
    bson_t *document;
    bson_oid_t oid;
    char *str;
    bson_error_t error;
    mongoc_collection_t *collection;

    int fail = EXIT_FAILURE;
    int time_out = 10;
    struct timespec ts;
    ts.tv_nsec = 100;

    printf("\nCreate connection...\n");

    fail = connection_init();

    while(fail)
    {
        time_out = time_out - 1;
        nanosleep(&ts, NULL);

        if(time_out == 0)
        {
            printf("Write time-out...\n");

            return EXIT_FAILURE;
        }

        printf("\nTrying again...\n");

        fail = connection_init();
    }

    printf("\nConnection Successfull...\n");
    
    collection = mongoc_client_get_collection(client, "admin", "posts");

    printf("\nCollection Success...\n");

    bson_oid_init(&oid, NULL);

    document = BCON_NEW(
        "_id", BCON_OID(&oid)
        ,"user", BCON_UTF8(username)
        ,"question", BCON_UTF8(question)
        ,"upvotes", BCON_INT32(0)
        ,"downvotes", BCON_INT32(0)
        ,"answers"
        ,"["
            ,"{"
                ,"userID", BCON_INT32(0)
                ,"answer", BCON_UTF8("No answer has been provided yet.")
                ,"upvotes", BCON_INT32(0)
                ,"downvotes", BCON_INT32(0)
            ,"}"
        ,"]"
    );

    printf("\nDocument Creation Success...\n");

    if(!mongoc_collection_insert_one(collection, document, NULL, NULL, &error))
    {
        fprintf(stderr, "%s\n", error.message);
    }
    else
    {
        str = bson_as_canonical_extended_json(document, NULL);
        printf("%s\n", str);
        bson_free(str);
    }

    mongoc_collection_destroy(collection);
    bson_destroy(document);
    cleanup_mongo();

    return EXIT_SUCCESS;

}



int _TEST_mongodb_write(char *question)
{
    bson_error_t error;
    bson_t *query;
    char *str;
    mongoc_cursor_t *cursor;
    mongoc_collection_t *collection;

    int fail = EXIT_FAILURE;
    int time_out = 10;
    struct timespec ts;
    ts.tv_nsec = 100;

    printf("\nCreate connection...\n");
    fail = connection_init();

    while(fail)
    {
        time_out = time_out - 1;
        nanosleep(&ts, NULL);

        if(time_out == 0)
        {
            printf("Write time-out...\n");
            return EXIT_FAILURE;
        }

        printf("\nTrying again...\n");
        fail = connection_init();
    }

    printf("\nConnection Successfull...\n");

    collection = mongoc_client_get_collection(client, "admin", "posts");

    printf("\nCollection Success...\n");

    query = bson_new();
    // BSON_APPEND_UTF8(query, "question", question);
    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);

    printf("\nQuery and Cursor Successfully created...\n");

    const bson_t *doc = query;

    while (mongoc_cursor_next(cursor, &doc)) 
    {
        str = bson_as_canonical_extended_json(query, NULL);
        printf("\n%s\n", str);
        bson_free(str);
    }

    printf("\nEnd query result...\n");

    bson_destroy(query);
    mongoc_collection_destroy(collection);
    cleanup_mongo();

    return EXIT_SUCCESS;
}



int main(int argc, char const *argv[])
{
    int fail;
    printf("\nBegin program...\n");

    // fail = write_to_mongo("Ben", "What is water?");

    // if(fail)
    // {
    //     printf("\nwrite_to_mongo FAILURE\n");
    //     return EXIT_FAILURE;
    // }
    // else
    // {
    //     printf("\nwrite_to_mongo Success...\n");
    // }
    

    fail = _TEST_mongodb_write("What is water?");

    if(fail)
    {
        printf("check_write_to_mongo FAILURE...\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("check_write_to_mongo SUCCESS...\n");
    }
    
    return EXIT_SUCCESS;
}