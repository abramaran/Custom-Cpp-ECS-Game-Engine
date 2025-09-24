#pragma once

struct RefreshGUIBarsEvent
{
    explicit RefreshGUIBarsEvent(std::size_t ID):  id{ID}{};

    std::size_t id;
};
