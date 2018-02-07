#pragma once

class SceneState;

class Scene
{
public:
    Scene();
    ~Scene();
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    virtual void enter();
    virtual void update();
    virtual void onMouseMove();
    void push(SceneState* state);
    void pop();
private:
    std::vector<SceneState*> m_stateStack;
    SceneState* m_currentState;
};
