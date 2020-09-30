#pragma once

class PerlinNoise
{
public:
	PerlinNoise();
	PerlinNoise( const double &persistence, const double &frequency, const double &amplitude, const int &octaves, const int &randomSeed );

	double GetHeight( const double &x, const double &y ) const;

	const double& GetPersistence() const;
	const double& GetFrequency() const;
	const double& GetAmplitude() const;
	const int& GetOctaves() const;
	const int& GetRandomSeed() const;

	void Set( const double &persistence, const double &frequency, const double &amplitude, const int &octaves, const int &randomseed );
	void SetPersistence( const double &persistence );
	void SetFrequency( const double &frequency );
	void SetAmplitude( const double &amplitude );
	void SetOctaves( const int &octaves );
	void SetRandomSeed( const int &randomSeed );

private:
	double Total( const double &i, const double &j ) const;
	double GetValue( const double &x, const double &y ) const;
	double Interpolate( const double &x, const double &y, const double &a ) const;
	double Noise( const int &x, const int &y ) const;

	double m_dPersistence, m_dFrequency, m_dAmplitude;
	int m_nOctaves, m_nRandomSeed;
};

inline const double& PerlinNoise::GetPersistence() const { return m_dPersistence; }
inline const double& PerlinNoise::GetFrequency() const { return m_dFrequency; }
inline const double& PerlinNoise::GetAmplitude() const { return m_dAmplitude; }
inline const int& PerlinNoise::GetOctaves() const { return m_nOctaves; }
inline const int& PerlinNoise::GetRandomSeed() const { return m_nRandomSeed; }

inline void PerlinNoise::Set( const double &persistence, const double &frequency, const double &amplitude, const int &octaves, const int &randomseed )
{
	m_dPersistence = persistence;
	m_dFrequency = frequency;
	m_dAmplitude = amplitude;
	m_nOctaves = octaves;
	m_nRandomSeed = randomseed;
}
inline void PerlinNoise::SetPersistence( const double &persistence ) { m_dPersistence = persistence; }
inline void PerlinNoise::SetFrequency( const double &frequency ) { m_dFrequency = frequency; }
inline void PerlinNoise::SetAmplitude( const double &amplitude ) { m_dAmplitude = amplitude; }
inline void PerlinNoise::SetOctaves( const int &octaves ) { m_nOctaves = octaves; }
inline void PerlinNoise::SetRandomSeed( const int &randomSeed ) { m_nRandomSeed = randomSeed; }