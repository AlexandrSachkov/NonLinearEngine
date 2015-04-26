#ifndef NL_DATA_REQUEST_TYPE_H_
#define NL_DATA_REQUEST_TYPE_H_

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			enum RequestType {ADD, REMOVE};

			struct MasterRequest
			{
				RequestType type;
				union Payload
				{
					uint_fast32_t index;
					double data;
				};
				Payload payload;
				
				MasterRequest()
				{
				}

				MasterRequest(RequestType typeVal, uint_fast32_t indexVal) :
					type(typeVal)
				{
					payload.index = indexVal;
				}

				MasterRequest(RequestType typeVal, double dataVal) :
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