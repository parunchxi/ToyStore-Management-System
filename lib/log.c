void saveLog(char user[], char action[], char status[], char detail[])
{
    FILE *logFile = fopen("../data/log.bin", "a");
    if (logFile == NULL)
    {
        perror("File could not be opened");
        return;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(logFile, "%d-%02d-%02d,%02d:%02d:%02d,%s,%s,%s,%s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, user, action, status, detail);
    fclose(logFile);
    return;
}