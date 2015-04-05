#ifndef NL_MESSAGE_H_
#define NL_MESSAGE_H_

namespace NLE
{
	namespace Core
	{
		template<typename T>
		class DataPacket
		{
		public:

			DataPacket() :
				_sysId(),
				_itemNumber(),
				_data()
			{
			}

			DataPacket(uint_fast8_t sysId, uint_fast8_t itemNumber, T data) :
				_sysId(sysId),
				_itemNumber(itemNumber),
				_data(data)
			{
			}

			~DataPacket()
			{
			}

			inline uint_fast8_t getSysId()
			{
				return _sysId;
			}

			inline uint_fast8_t getItemNumber()
			{
				return _itemNumber;
			}

			inline T getData()
			{
				return _data;
			}

		private:
			uint_fast8_t _sysId;
			uint_fast8_t _itemNumber;
			T _data;
		};
	}
}

#endif