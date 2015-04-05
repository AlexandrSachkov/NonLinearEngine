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

			uint_fast8_t getSysId()
			{
				return _sysId;
			}

			uint_fast8_t getItemNumber()
			{
				return _itemNumber;
			}

			T getData()
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