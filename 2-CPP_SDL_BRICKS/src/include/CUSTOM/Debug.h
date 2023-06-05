namespace Debug
{

    template <typename T>

    void Log(T sth)
    {
        printf(to_string(sth).c_str());
    }

    void LogMsg(string sth)
    {
        printf(sth.c_str());
    }

} // namespace Debug
