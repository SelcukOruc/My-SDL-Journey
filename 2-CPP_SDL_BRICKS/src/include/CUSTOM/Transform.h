struct Transform
{
public:
    string _objectName;
    int m_ID = 0;
    Vector2 position = {0, 0};
    Vector2 scale = {0, 0};

    Transform()
    {
        IsSelected = false;
        ObjectNumberCreated++;
        m_ID = ObjectNumberCreated;
        _objectName = "GameObject_ " + to_string(m_ID);
    }

private:
    bool IsSelected;
    bool IsHovering()
    {
        return (GetMousePosition().x >= position.x && GetMousePosition().x < position.x + scale.x && GetMousePosition().y >= position.y && GetMousePosition().y < position.y + scale.y);
    }

public:
    void EditorMode()
    {
        if (IsHovering() && IsMouseButtonDown(0))
        {
            if (IsSelected == false)
            {
                IsSelected = true;
                cout << "SELECTED OBJECT NAME : " + _objectName << endl;
                cout << "CURRENT X : " + to_string(position.x) + " CURRENT Y : " + to_string(position.y) << endl;
            }
            else
            {
                IsSelected = false;
                cout << "NEW X : " + to_string(position.x) + " NEW Y : " + to_string(position.y) << endl;
            }
        }

        if (IsSelected)
        {
            position = Vector2{GetMousePosition().x, GetMousePosition().y};

            if (OnKeyDown(SDL_SCANCODE_KP_8))
                scale.y += 5;
            else if (OnKeyDown(SDL_SCANCODE_KP_2))
                scale.y -= 5;
            else if (OnKeyDown(SDL_SCANCODE_KP_4))
                scale.x += 5;
            else if (OnKeyDown(SDL_SCANCODE_KP_6))
                scale.x -= 5;
            else if (OnKeyDown(SDL_SCANCODE_KP_0))
                cout << " CURRENT Width[X] : " + to_string(scale.x) + "CURRENT Height[Y] : " + to_string(scale.y) << endl;
        }
    }
};
