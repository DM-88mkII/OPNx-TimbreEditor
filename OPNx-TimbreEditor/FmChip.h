#pragma once



#include <queue>
#include "ymfm/ymfm_opn.h"



#define LOG_WRITES (0)
#define EXTRA_CLOCKS (0)



using emulated_time = int64_t;



enum EChipType
{
	YM2203,
};



class FmChipBase
{
	public:
		virtual ~FmChipBase(){}
		
		FmChipBase(uint32_t clock, EChipType type):m_type(type){}
		
		EChipType type() const { return m_type; }
		virtual uint32_t sample_rate() const = 0;
		
		virtual void write(uint32_t reg, uint8_t data) = 0;
		virtual void generate(emulated_time output_start, emulated_time output_step, int32_t *buffer) = 0;
	
	protected:
		EChipType m_type;
};



template<typename ChipType>
class FmChip : public FmChipBase, public ymfm::ymfm_interface
{
	public:
		FmChip(uint32_t clock, EChipType type)
		:FmChipBase(clock, type)
		,m_chip(*this)
		,m_clock(clock)
		,m_clocks(0)
		,m_step(0x100000000ull / m_chip.sample_rate(clock))
		,m_pos(0)
		{
			m_chip.reset();
			
			for (int clock = 0; clock < EXTRA_CLOCKS; clock++){
				m_chip.generate(&m_output);
			}
		}
		
		
		
		virtual uint32_t sample_rate() const override
		{
			return m_chip.sample_rate(m_clock);
		}
		
		
		
		virtual void write(uint32_t reg, uint8_t data) override
		{
			m_queue.push(std::make_pair(reg, data));
		}
		
		
		
		virtual void generate(emulated_time output_start, emulated_time output_step, int32_t *buffer) override
		{
			uint32_t addr1 = 0xffff, addr2 = 0xffff;
			uint8_t data1 = 0, data2 = 0;
			
			if (!m_queue.empty()){
				auto front = m_queue.front();
				addr1 = 0 + 2 * ((front.first >> 8) & 3);
				data1 = front.first & 0xff;
				addr2 = addr1 + 1;//addr2 = addr1 + ((m_type == CHIP_YM2149) ? 2 : 1);
				data2 = front.second;
				m_queue.pop();
			}
			
			if (addr1 != 0xffff){
				m_chip.write(addr1, data1);
				m_chip.write(addr2, data2);
			}
			
			for (; m_pos <= output_start; m_pos += m_step){
				m_chip.generate(&m_output);
			}
			
			if (m_type == YM2203){
				int32_t out0 = m_output.data[0];
				int32_t out1 = m_output.data[1 % ChipType::OUTPUTS];
				int32_t out2 = m_output.data[2 % ChipType::OUTPUTS];
				int32_t out3 = m_output.data[3 % ChipType::OUTPUTS];
				*buffer++ += out0 + out1 + out2 + out3;
				//*buffer++ += out0 + out1 + out2 + out3;
			}
			m_clocks++;
		}
	
	protected:
		virtual uint8_t ymfm_external_read(ymfm::access_class type, uint32_t offset) override { return 0; }
		
		ChipType m_chip;
		uint32_t m_clock;
		uint64_t m_clocks;
		typename ChipType::output_data m_output;
		emulated_time m_step;
		emulated_time m_pos;
		std::queue<std::pair<uint32_t, uint8_t>> m_queue;
};
