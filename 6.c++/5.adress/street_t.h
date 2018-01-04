#ifndef __STREET_T_H__
#define __STREET_T_H__

#include <iostream>
#include <vector>

template <class T1, class T2>
class Street_t
{
	public:
		Street_t (const T1& _id);
		~Street_t ();
		Street_t(const Street_t<T1,T2>& _street);
		Street_t& operator=(const Street_t<T1,T2>& _street);
		T1 GetStreedId() const;
		void SetStreetId(const T1& _id);
		void AddBuildingToStreet(const Building_t<T2>& _building);
		Building_t<T2>& GetBuilding(T2& _buildingId);

	private:
		/* data */
		T1 m_streetId;
		std::vector<Building_t<T2>*> m_buildings;
};

/*-----------------------------*/

template <class T1, class T2>
Street_t<T1,T2>::Street_t(const T1& _id)
{
	m_streetId = _id;
}

/*-----------------------------*/

template <class T1, class T2>
Street_t<T1,T2>::~Street_t ()
{
	delete m_buildings;
}

/*-----------------------------*/

template <class T1, class T2>
Street_t<T1,T2>::Street_t(const Street_t<T1,T2>& _street)
{
	m_buildings = _street.m_buildings;
	if(NULL == m_buildings)
	{
		//TODO something
	}
	
	m_streetId = _street.m_streetId;
}

/*-----------------------------*/

template <class T1, class T2>
Street_t<T1,T2>& Street_t<T1,T2>::operator=(const Street_t<T1,T2>& _street)
{
	m_streetId = _street.m_streetId;
	m_buildings = _street.m_buildings;
}

/*------------------------------*/

template <class T1, class T2>
T1& Street_t<T1,T2>::GetStreedId() const
{
	return m_streetId;
}

/*------------------------------*/

template <class T1, class T2>
void Street_t<T1,T2>::SetStreetId(const T1& _id)
{
	m_streetId = _id;
}

/*-------------------------------*/

template <class T1, class T2>
void Street_t<T1,T2>::AddBuildingToStreet(const Building_t<T2>& _building)
{
	m_buildings.insert(_building, m_buildings.end());
}

/*-------------------------------*/

template <class T1, class T2>
Building_t<T2>& Street_t<T1,T2>::GetBuilding(T2& _buildingId)
{
	for(size_t i = 0; i < m_buildings.size(); ++i)
	{
		if(m_buildings[i].GetBuildingId() == _buildingId)
		{
			return m_buildings[i];
		}
	}
}

/*--------------------------------*/



#endif /* __STREET_T_H__ */

