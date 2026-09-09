#include "pch.h"
#include "Enemy.h"
#include "SoundEffect.h"
#include "Texture.h"
#include "utils.h"

Enemy::Enemy(Vector2f position, BulletManager* bulletManager, Player* player)
    :m_EnemyPosition{position}
    ,m_BulletManagerPtr{bulletManager}
    ,m_PlayerPtr{player}
{
    m_DeathSoundPtr = new SoundEffect{ "Sound/Enemy/Enemy_Die.wav" };
    m_EnemyExplosionTexturePtr = new Texture{ "Enemy/EnemyExplosion.png" };
}

Enemy::~Enemy()
{
    delete m_EnemyExplosionTexturePtr;
    m_EnemyExplosionTexturePtr = nullptr;

    delete m_DeathSoundPtr;
    m_DeathSoundPtr = nullptr;

    delete m_EnemyTexturePtr;
    m_EnemyTexturePtr = nullptr;
}

void Enemy::Draw() const
{
    if (m_Dead && !m_Exploded)
    {
        glPushMatrix();
        {
            float scale{ 3 };
            glTranslatef(m_EnemyPosition.x + m_EnemyWidth / 2, m_EnemyPosition.y + m_EnemyHeight / 2, 0);
            glScalef(scale, scale, 0);

            Rectf drawBox{ (m_EnemyExplosionTexturePtr->GetWidth() / 7) * static_cast<int>(m_CurrentFrame), 0, m_EnemyExplosionTexturePtr->GetWidth() / 7, m_EnemyExplosionTexturePtr->GetHeight() };
            m_EnemyExplosionTexturePtr->Draw(Vector2f{ 0,0 }, drawBox);
        }
        glPopMatrix();
    }
}

void Enemy::Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
    if (m_Dead && !m_Exploded)
    {
        if (!m_ExplosionSoundStarted)
        {
            m_DeathSoundPtr->Play(false);
            m_ExplosionSoundStarted = true;
        }

        m_CurrentFrame += 10 * elapsedSec;
        if (m_CurrentFrame >= 7)
        {
            m_Exploded = true;
        }
    }
}

void Enemy::Hit(int damage)
{
    m_Health -= damage;
}

Rectf Enemy::GetEnemyHitBox() const
{
    return m_EnemyHitBox;
}

int Enemy::GetHealth() const
{
    return m_Health;
}

bool Enemy::GetActive() const
{
    return m_Active;
}

void Enemy::SetVolume(int Volume) const
{
    m_DeathSoundPtr->SetVolume(Volume);
}

bool Enemy::HitEntity(const Rectf& entityHitBox)
{
    if (utils::IsOverlapping(entityHitBox, m_EnemyHitBox))
    {
        return true;
    }
    else
    {
        return false;
    }
}