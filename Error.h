#pragma once

namespace flyzero
{
    enum class ErrorCode
    {
        FZ_SUCCESS = 0,
        FZ_NO_BUFFER,			// �ṩ�Ļ������ռ䲻��
        FZ_NO_MEMORY,			// �ڴ治��
        FZ_INVALID_PARAM		// ��Ч����		
    };
}