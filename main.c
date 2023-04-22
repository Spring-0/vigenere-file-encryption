#include <stdio.h>
#include <string.h>


int encrypt(char *filePath, char *key){

    FILE *outputFile = fopen("encrypted.txt", "w");
    FILE *inputFile = fopen(filePath, "r");

    if(outputFile == NULL){
        printf("Could not create output file.\n");
        return 1;
    }

    if(inputFile == NULL){
        printf("Could not open file '%s'\n", filePath);
        return 1;
    }

    char ch;
    int keyWrapCounter = 0;

    while((ch = fgetc(inputFile)) != EOF){
        ch += key[keyWrapCounter];

        if(keyWrapCounter > strlen(key)){
            keyWrapCounter = 0;
        } else{
            keyWrapCounter++;
        }

        fputc(ch, outputFile);

    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;

}

int decrypt(char* encryptedFilePath, char* key){

    FILE *inputFile = fopen(encryptedFilePath, "r");
    FILE *outputFile = fopen("decrypted-file.txt", "w");

    if(inputFile == NULL || outputFile == NULL){
        printf("Error accessing file.");
        return 1;
    }

    char ch;
    int keyWrapCounter = 0;
    while((ch = getc(inputFile)) != EOF){
        ch -= key[keyWrapCounter];

        if(keyWrapCounter > strlen(key)){
            keyWrapCounter = 0;
        } else{
            keyWrapCounter++;
        }

        fputc(ch, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;

}


int main() {
    int done = 0;
    int userSelection;
    const char prompt[] = "Enter operation:\n     1. Encrypt\n     2. Decrypt\n     3. Quit";

    while (!done){

        char filePath[255];
        char key[255];

        puts(prompt);
        scanf("%d", &userSelection);

        switch(userSelection){
            case 1:
                printf("Enter file path to encrypt:\n");
                scanf("%255s", filePath);
                printf("Enter key to encrypt file with:\n");
                scanf("%255s", key);

                // Error has occurred.
                if(encrypt(filePath, key) == 1){
                    continue;
                }

                printf("Successfully decrypted '%s' with the key '%s'.\n", filePath, key);
                break;

            case 2:
                printf("Enter file path to decrypt:\n");
                scanf("%255s", filePath);
                printf("Enter key to decrypt path with:\n");
                scanf("%255s", key);

                // Error has occurred.
                if(decrypt(filePath, key) == 1){
                    continue;
                }

                printf("Successfully decrypted '%s' with the key '%s'.\n", filePath, key);
                break;

            case 3:
                printf("Exiting, goodbye...");
                done = 1;

            default:
                printf("Invalid Operation.\n");
                getchar(); // digest character
                continue;
        }
    }
    return 0;
}
