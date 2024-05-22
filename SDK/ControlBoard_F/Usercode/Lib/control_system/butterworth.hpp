#pragma once

#include "z_tf.hpp"

template <typename T>
class Butter_LP_30_120_40dB_50000Hz : public control_system::DiscreteControllerBase<T>
{
private:
    control_system::ZTf<T> section1{{1, 2, 1},
                                    {1,
                                     -1.996334124749842731105786697298754006624,
                                     0.996356824194989720844262137688929215074}};
    T gain1 = 0.000005674861286727915591623569446788622;

    control_system::ZTf<T> section2{{1, 2, 1},
                                    {1,
                                     -1.991204554190161069016085093608126044273,
                                     0.991227195309197228745290431106695905328}};
    T gain2 = 0.000005660279759003780935145561103993828;

public:
    T Step(T input) override
    {
        return gain1 * section1.Step(gain2 * section2.Step(input));
    }

    void ResetState() override
    {
        section1.ResetState();
        section2.ResetState();
    }
};

// 2 个 section 及以上的建议使用 double 计算
template <typename T>
class Butter_LP_5_20_40dB_5000Hz : public control_system::DiscreteControllerBase<T>
{
private:
    control_system::ZTf<T> section1{{1, 2, 1},
                                    {1,
                                     -1.99387228140026384615168808522867038846,
                                     0.993935262537587349562784311274299398065}};
    T gain1 = 0.000015745284330885315826143236450640472;

    control_system::ZTf<T> section2{{1, 2, 1},
                                    {1,
                                     -1.985358237412071291672077677503693848848,
                                     0.985420949613325825033882665593409910798}};
    T gain2 = 0.000015678050313616359134720468215817846;

public:
    T Step(T input) override
    {
        return gain1 * section1.Step(gain2 * section2.Step(input));
    }

    void ResetState() override
    {
        section1.ResetState();
        section2.ResetState();
    }
};

template <typename T>
class Butter_LP_5_50_20dB_5000Hz : public control_system::DiscreteControllerBase<T>
{
private:
    control_system::ZTf<T> section1{{1, 2, 1},
                                    {1,
                                     -1.971823537253104108302181884937454015017,
                                     0.972215016838654855213519567769253626466}};
    T gain1 = 0.000097869896387716434973946810771394667;

public:
    T Step(T input) override
    {
        return gain1 * section1.Step(input);
    }

    void ResetState() override
    {
        section1.ResetState();
    }
};

template <typename T>
class Butter_LP_5_50_20dB_1000Hz : public control_system::DiscreteControllerBase<T>
{
private:
    control_system::ZTf<T> section1{{1, 2, 1},
                                    {1,
                                     -1.858313796423278541070089886488858610392,
                                     0.867707845059007443211385179893113672733}};
    T gain1 = 0.002348512158932234642622072229301011248;

public:
    T Step(T input) override
    {
        return gain1 * section1.Step(input);
    }

    void ResetState() override
    {
        section1.ResetState();
    }
};

template <typename T>
class Butter_LP_5_50_20dB_3000Hz : public control_system::DiscreteControllerBase<T>
{
private:
    control_system::ZTf<T> section1{{1, 2, 1},
                                    {1,
                                     -1.953019802626017265012592361017595976591,
                                     0.954098328230158609919442369573516771197}};
    T gain1 = 0.000269631401035287600245066164106333417;

public:
    T Step(T input) override
    {
        return gain1 * section1.Step(input);
    }

    void ResetState() override
    {
        section1.ResetState();
    }
};
