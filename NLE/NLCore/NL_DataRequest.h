#ifndef NL_DATA_REQUEST_TYPE_H_
#define NL_DATA_REQUEST_TYPE_H_

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			enum RequestType {ADD, REMOVE};

			template<typename T>
			struct MasterRequest
			{
				RequestType type;

				template<typename T>
				union Payload
				{
					uint_fast32_t index;
					T data;
				};
				Payload<T> payload;
				
				MasterRequest()
				{
				}

				MasterRequest(RequestType typeVal, uint_fast32_t indexVal) :
					type(typeVal)
				{
					payload.index = indexVal;
				}

				MasterRequest(RequestType typeVal, T dataVal) :
					type(typeVal)
				{
					payload.data = dataVal;
				}
			};

			struct DistributorRequest
			{
				RequestType type;
				uint_fast32_t index;
			};
		}
	}
}

#endif