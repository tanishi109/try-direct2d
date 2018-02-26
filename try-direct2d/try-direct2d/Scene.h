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
    void pop(unsigned int times = 1);
    bool findHistory(const type_info& typeInfo);
private:
    std::vector<std::shared_ptr<SceneState>> m_stateStack;
    SceneState* m_currentState;
};
