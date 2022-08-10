#include "adc.hpp"

namespace ADC
{
    bool ADC_CONTROLL::_checkCalFuse()
    {
        esp_err_t status{ESP_OK};
        bool cali_enable = false;

        status = esp_adc_cal_check_efuse(ADC_CALI_SCHEME);
        if (ESP_OK == status)
        {
            cali_enable = true;
            esp_adc_cal_characterize(ADC_UNIT_1, _adcAttenuation, _bitWidth, 0, &_adc1_characteristics);
        }
        return cali_enable;
    }

    ADC_CONTROLL::ADC_CONTROLL(adc1_channel_t channel)
    {
        SetChannel(channel);
    }

    void ADC_CONTROLL::SetChannel(adc1_channel_t channel)
    {
        _adc1Channel = channel;
        adc1_config_width(_bitWidth);
        adc1_config_channel_atten(_adc1Channel, _adcAttenuation);

        _calEnabled = _checkCalFuse();
    }

    bool ADC_CONTROLL::CheckCalFuse()
    {
        return _checkCalFuse();
    }

    int ADC_CONTROLL::GetRaw()
    {
        return adc1_get_raw(_adc1Channel);
    }

    int ADC_CONTROLL::GetVoltage()
    {
        if (_calEnabled)
        {
            return esp_adc_cal_raw_to_voltage(adc1_get_raw(_adc1Channel), &_adc1_characteristics);
        }
        else
        {
            return -1;
        }
    }

    esp_err_t ADC_CONTROLL::SetBitWidth(adc_bits_width_t bitWidth)
    {
        _bitWidth = bitWidth;
        _calEnabled = _checkCalFuse();
        return adc1_config_width(_bitWidth);
    }

    esp_err_t ADC_CONTROLL::SetBitWidth(int bitWidth)
    {
        switch (bitWidth)
        {
        case 9:
            _bitWidth = ADC_WIDTH_BIT_9;
            break;
        case 10:
            _bitWidth = ADC_WIDTH_BIT_10;
            break;
        case 11:
            _bitWidth = ADC_WIDTH_BIT_11;
            break;
        case 12:
            _bitWidth = ADC_WIDTH_BIT_12;
            break;
        default:
            _bitWidth = ADC_WIDTH_MAX;
            break;
        }

        _calEnabled = _checkCalFuse();
        return adc1_config_width(_bitWidth);
    }

    esp_err_t ADC_CONTROLL::SetAttenuation(adc_atten_t attenuation)
    {
        _adcAttenuation = attenuation;
        _calEnabled = _checkCalFuse();
        return adc1_config_channel_atten(_adc1Channel, _adcAttenuation);
    }

} // CPPANALOG namespace