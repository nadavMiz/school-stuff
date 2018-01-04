#ifndef __BUILDING_T_H__
#define __BUILDING_T_H__

template <class T>
class Building_t
{
	public:
		Building_t (const T& _id);
		~Building_t(){};
		Building_t (const Building_t<T>& _building);
		Building_t& operator=(const Building_t<T>& _building);
		
		T GetBuildingId() const;
		void SetBuildingId(const T& _id);

	private:
		/* data */
		T m_buildingId;
};

template <class T>
Building_t<T>::Building_t(const T& _id)
{
	m_buildingId = _id;
}

template <class T>
Building_t<T>::Building_t(const Building_t& _building)
{
	m_buildingId = _building.m_buildingId;
}

template <class T>
Building_t<T>& Building_t<T>::operator=(const Building_t& _building)
{
	m_buildingId = _building.m_buildingId;
}

template <class T>
T Building_t<T>::GetBuildingId() const
{
	return m_buildingId;
}

template <class T>
void Building_t<T>::SetBuildingId(const T& _id)
{
	m_buildingId = _id;
}

#endif /* __BUILDING_T_H__ */

