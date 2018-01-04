#ifndef __CITY_H_H__
#define __CITY_H_H__

template <class C, class S, class B>
class City_t
{
	public:
		City_t (C& _cityId);
		~city_t (){};
		City_t(const City_t<C,S,B>& _city);
		City_t& operator=(const City_t<C,S,B>& _city);
		C GetCityId() const;
		void SetCityId(const C& _cityId);
		void AddStreet(const Street_t<S,B>& _street);
		Street_t<S,B>& GetStreet(const S& _streetId);

	private:
		/* data */
		C m_cityId;
		std::vector<Street_t<S,B>*> m_streets;
};

template <class C, class S, class B>
City_t<C,S,B>::City_t (C& _cityId)
{
	m_cityId = _cityId;
}

/*------------------------------*/

template <class C, class S, class B>
City_t<C,S,B>& City_t<C,S,B>::operator=(const City_t<C,S,B>& _city)
{
	m_cityId = _city.m_cityId;
	m_streets = _city.m_streets;
}

/*--------------------------------*/

template <class C, class S, class B>
City_t<C,S,B>::City_t(const City_t<C,S,B>& _city)
{
	*this = _city;
}

/*------------------------------*/

template <class C, class S, class B>
C City_t<C,S,B>::GetCityId() const
{
	return m_cityId;
}

/*-----------------------------*/

#endif /* __CITY_H_H__ */

