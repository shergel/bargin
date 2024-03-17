#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace bgn
{
    class Controller final
    {
    public:
        explicit Controller(unsigned int id);
        ~Controller();
        Controller(const Controller& other) = delete;
        Controller(Controller&& other) = delete;
        Controller& operator=(const Controller& other) = delete;
        Controller& operator=(Controller&& other) = delete;

        void Update();
        glm::vec2 GetThumbL2D() const;
        glm::vec2 GetThumbR2D() const;
        glm::vec2 GetDPad2D() const;
        bool IsDown(unsigned int button) const;
        bool IsPressed(unsigned int button) const;
        bool IsUp(unsigned int button) const;
        bool IsStateChanged() const;
        void SetDeadzone(const float deadzone);

    private:
        class Impl;
        std::unique_ptr<Impl> m_pimpl;
    };
}
