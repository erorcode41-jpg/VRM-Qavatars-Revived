#pragma once
#include "main.hpp"

namespace ArrayUtils {
    //borrowed from QuestUI (kept: pure helper)
    template <class Out, class T, class Predicate>
    inline std::vector<Out> Select(std::vector<T> array, Predicate pred)
    {
        std::vector<Out> newArray(array.size()); 
        for (int i = 0; i < array.size(); i++) { 
            newArray[i] = pred(array[i]); 
        } 
        return newArray;
    }
}

// Replacement for il2cpp_utils::vectorToArray (removed/changed in beatsaber-hook 6).
// Returns a proxy that converts to whatever ArrayW<T> the callee expects.
template <typename In>
struct VecToArrayProxy {
    const std::vector<In>& v;
    template <typename Out>
    operator ArrayW<Out>() const {
        ArrayW<Out> arr(v.size());
        for (size_t i = 0; i < v.size(); i++) arr[i] = static_cast<Out>(v[i]);
        return arr;
    }
};
template <typename In>
inline VecToArrayProxy<In> VecToArray(const std::vector<In>& v) { return {v}; }
