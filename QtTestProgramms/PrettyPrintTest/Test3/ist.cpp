	if (1)
	{
		liTime.QuadPart = (LONGLONG)((((TimeStamp.dftSecBetween1601and1970 () + 
			(double)m_ReferenceTime.time + dQueryTimer) * 1000.) + 
			(double)m_ReferenceTime.millitm) * 10000.);
	}else
	{
		liTime.QuadPart = (LONGLONG)(dQueryTimer * 1e+7);
	}